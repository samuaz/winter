//
// Created by AZCONA VARGAS, SAMUEL EDUARDO [AG-Contractor/5000] on 2019-10-08.
//

#include <wintercpp/boot/winter_boot.h>

using namespace winter;

std::unique_ptr<WinterBoot> WinterBoot::instance_;
std::once_flag              WinterBoot::m_once_;
ServerBuilder               WinterBoot::builder_;

void WinterBoot::init(const std::string &host, const std::string &port) {
    getInstance();
    runServer(host, port);
}

void WinterBoot::registerController(grpc::Service *controller) {
    builder_.RegisterService(controller);
}

void WinterBoot::runServer(const std::string &host, const std::string &port) {
    /// server address

    std::string server_address(host + ":" + port);

    //// Listen on the given address without any authentication mechanism.
    //// security is service independent by security module
    //// you can also make this use ssl security or auth
    builder_.AddListeningPort(server_address,
                              grpc::InsecureServerCredentials());
    builder_.SetSyncServerOption(
        grpc::ServerBuilder::SyncServerOption::CQ_TIMEOUT_MSEC, 900000);

    /// Register "service" as the Instance through which we'll communicate with
    /// clients. In this case it corresponds to an *synchronous* service.

    /// Finally assemble the server.
    std::unique_ptr<Server> server(builder_.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    /// Wait for the server to shutdown. Note that some other thread must be
    /// responsible for shutting down the server for this call to ever return.
    server->Wait();
}

WinterBoot::~WinterBoot() = default;

void WinterBoot::onInit(const std::string           &host,
                        const std::string           &port,
                        const std::function<void()> &initFunction) {
    initFunction();
    init(host, port);
}

WinterBoot::WinterBoot() = default;
