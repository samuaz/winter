#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

// docker contaienr constants
const std::string MARIA_DB_TAG = "10.5";
const std::string MARIA_DB_USER = "winter_test";
const std::string MARIA_DB_PASSWORD = "winter_test";
const std::string MARIA_DB_IMAGE_NAME = "mariadb";
const std::string MARIA_DB_ROOT_USER = "root";
const std::string MARIA_DB_ROOT_PASSWORD = "winter_test";
const std::string MARIA_DB_SCHEMA_NAME = "winter_test";
const int         timeout = 300;  // 5 minutes timeout

// Check if docker container is ready and also if mysql is ready to accept connections
inline bool isMariaDBReady(std::string containerName, std::string host, std::string port, int timeout) {
    std::string           inspectCommand = "docker inspect -f {{.State.Running}} " + containerName;
    std::string           result = "";
    char                  buffer[1024];
    std::shared_ptr<FILE> pipe(popen(inspectCommand.c_str(), "r"), pclose);
    if (! pipe) return false;
    auto start = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start < std::chrono::seconds(timeout)) {
        if (! feof(pipe.get())) {
            if (fgets(buffer, 1024, pipe.get()) != nullptr) {
                result += buffer;
            }
        }
        if (std::strcmp(result.c_str(), "true\n") == 0) {
            // Check if the container is running and mariadb is ready to accept connections
            std::string checkCommand2 = "docker exec " + containerName + " mysql" + " -h " + host + " -P " + port + " -u " + MARIA_DB_ROOT_USER + " -p" + MARIA_DB_ROOT_PASSWORD + " -e 'select 0' --silent";
            std::cout << checkCommand2 << std::endl;
            int ret = std::system(checkCommand2.c_str());
            if (ret == 0) {
                // return true if mariadb is ready for connections
                return true;
            }
        }
        // wait for 1 sec before retry
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // timeout
    return false;
}

// generate a random port number for the container to allow multiple tests in parallel
inline int generatePortNumber() {
    std::random_device              rd;
    std::mt19937                    eng(rd());
    std::uniform_int_distribution<> distr(40000, 49999);
    return distr(eng);
}

// generate a random container name for the container to allow multiple tests in parallel
inline std::string generateContainerName() {
    std::string                     containerName = "winter-mariadb-container-";
    std::random_device              rd;
    std::mt19937                    eng(rd());
    std::uniform_int_distribution<> distr(0, 9999);
    containerName += std::to_string(distr(eng));
    return containerName;
}

// Test fixture for gtest
class WithMariaDBDatabase : public ::testing::Test {
   public:
    std::string containerName;
    int         portNumber;

    // save the current port
    WithMariaDBDatabase() {
        portNumber = generatePortNumber();
    }

    // Execute Mariadb docker before each test
    void SetUp() override {
        // Generar un nombre de contenedor aleatorio
        containerName = generateContainerName();

        // command to run mariadb docker container
        std::string runCommand = "docker run -d --name " + containerName + " -p " + std::to_string(portNumber) + ":3306 -e MYSQL_ROOT_PASSWORD=" + MARIA_DB_ROOT_PASSWORD + " -e MYSQL_USER=" + MARIA_DB_USER + " -e MYSQL_PASSWORD=" + MARIA_DB_PASSWORD + " -e MYSQL_DATABASE=" + MARIA_DB_SCHEMA_NAME + " " + MARIA_DB_IMAGE_NAME + ":" + MARIA_DB_TAG;

        std::system(runCommand.c_str());

        if (isMariaDBReady(containerName, "localhost", std::to_string(portNumber), timeout)) {
            std::cout << "MariaDB is running and ready to accept connections " << containerName << std::endl;
        } else {
            std::cout << "MariaDB db is not running timeout exceed, exiting " << containerName << std::endl;
            TearDown();
            ASSERT_TRUE(false);
        }
    }

    // stop and clean docker container
    void TearDown() override {
        std::cout << "Limpiando test " << containerName << std::endl;
        // stop and remove mariadb docker container
        std::string stopCommand = "docker stop " + containerName;
        std::string rmCommand = "docker rm " + containerName;
        std::system(stopCommand.c_str());
        std::system(rmCommand.c_str());
    }
};

#include <functional>

class ScopedGuard {
   public:
    explicit ScopedGuard(std::function<void()> on_exit_scope) :
        on_exit_scope_(on_exit_scope), dismissed_(false) {}

    ~ScopedGuard() {
        if (! dismissed_) {
            on_exit_scope_();
        }
    }

    void dismiss() {
        dismissed_ = true;
    }

   private:
    std::function<void()> on_exit_scope_;
    bool                  dismissed_;
};