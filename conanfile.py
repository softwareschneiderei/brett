from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.files import copy


class BrettConan(ConanFile):
    name = "brett"
    version = "0.2"
    license = "MIT"
    author = "Marius Elvert marius.elvert@softwareschneiderei.de"
    url = "https://github.com/softwareschneiderei/brett"
    description = "Useful C++ components for application development."
    topics = ("utilities",)
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "CMakeDeps"
    exports_sources = "src/*", "include/*", "tests/*", "CMakeLists.txt"
    test_requires = "catch2/2.13.10",

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package_info(self):
        self.cpp_info.libs = ["brett"]
        if self.settings.os == "Linux":
            self.cpp_info.libs += ["pthread"]
