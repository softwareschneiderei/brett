from conans import ConanFile, CMake, tools


class BrettConan(ConanFile):
    name = "Brett"
    version = "0.1"
    license = "MIT"
    author = "Marius Elvert marius.elvert@softwareschneiderei.de"
    url = "https://github.com/softwareschneiderei/brett"
    description = "Useful C++ components for application development."
    topics = ("utilities",)
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*", "include/*", "tests/*", "CMakeLists.txt"
    build_requires = "Catch2/2.7.2@catchorg/stable",

    def _configured_cmake(self):
        cmake = CMake(self)
        cmake.configure(source_folder=".")
        return cmake

    def build(self):
        self._configured_cmake().build()

    def package(self):
        self._configured_cmake().install()

    def package_info(self):
        self.cpp_info.libs = ["brett"]
