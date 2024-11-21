from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.files import copy
import os

class WintercppMysqlCoreRecipe(ConanFile):
    name = "wintercpp_mysql_core"
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
        self.requires("openssl/[>=1.1.1 <4]")
        self.requires("wintercpp_core/1.0")

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
        copy(self, "include", self.source_folder, os.path.join(self.package_folder, "include"))

    def package_info(self):
        self.cpp_info.includedirs = ["include"]
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []
        self.cpp_info.requires = ["openssl::openssl", "wintercpp_core::wintercpp_core"]
        wintercpp_core_include_dir = self.dependencies["wintercpp_core"].cpp_info.includedirs[0]
        openssl_include_dir = self.dependencies["openssl"].cpp_info.includedirs[0]
        self.cpp_info.includedirs.append(wintercpp_core_include_dir)
        self.cpp_info.includedirs.append(openssl_include_dir)
