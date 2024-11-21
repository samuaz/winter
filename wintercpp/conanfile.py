from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps

class WintercppCoreRecipe(ConanFile):
    name = "wintercpp_core"
    version = "1.0"

    # Optional metadata
    license = "MIT"
    author = "AZCONA VARGAS, SAMUEL EDUARDO <email@example.com>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "winterc++ core framework to build microservices using cpp"
    topics = ("microservices", "cpp")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*", "dependencies.cmake", "cmake/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def requirements(self):
        self.requires("nlohmann_json/3.11.3")
        self.requires("cpp-jwt/1.4")
        self.requires("gtest/1.14.0")
        self.requires("openssl/[>=1.1.1 <4]")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["wintercpp_core"]
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.requires = ["openssl::openssl", "nlohmann_json::nlohmann_json", "cpp-jwt::cpp-jwt", "gtest::gtest"]
        openssl_include_dir = self.dependencies["openssl"].cpp_info.includedirs[0]
        nlohmann_json_include_dir = self.dependencies["nlohmann_json"].cpp_info.includedirs[0]
        cpp_jwt_include_dir = self.dependencies["cpp-jwt"].cpp_info.includedirs[0]
        gtest_include_dir = self.dependencies["gtest"].cpp_info.includedirs[0]
        self.cpp_info.includedirs.append(nlohmann_json_include_dir)
        self.cpp_info.includedirs.append(cpp_jwt_include_dir)
        self.cpp_info.includedirs.append(gtest_include_dir)
        self.cpp_info.includedirs.append(openssl_include_dir)
        #self.dependencies["cpp-jwt"].cpp_info.includedirs.append(nlohmann_json_include_dir)
