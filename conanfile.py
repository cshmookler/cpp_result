"""cpp_result root Conan file"""

import os

from conan import ConanFile
from conan.tools.meson import Meson, MesonToolchain


required_conan_version = ">=2.3.0"


class cpp_result(ConanFile):

    # Required
    name = "cpp_result"

    # Metadata
    license = "Zlib"
    author = "Caden Shmookler"
    url = "https://github.com/cshmookler/cpp_result"
    description = "A compromise between error codes and exceptions. Contains result types with detailed error messages and stack traces."
    topics: list = []

    # Configuration
    package_type = "application"
    settings = "os", "compiler", "build_type", "arch"
    build_policy = "missing"

    # Files needed by Conan to resolve version and dependencies
    exports = ("VERSION",)

    # Files needed by Conan to build from source
    exports_sources = (
        "VERSION",
        os.path.join("include", "*"),
        os.path.join("tests", "*"),
        os.path.join("examples", "*"),
        "meson.build",
    )

    def set_version(self):
        """Get project version from the VERSION file"""

        with open("VERSION") as file:
            self.version = file.readline().strip()

    def build_requirements(self):
        """Declare dependencies of the build system"""

        self.tool_requires("meson/1.6.0")

    def requirements(self):
        """Resolve and declare dependencies"""

        # This project does not have any build dependencies.

    def layout(self):
        """Set the layout of the build files"""

        self.folders.build = os.path.join(self.recipe_folder, "build")
        self.folders.generators = os.path.join(self.folders.build, "generators")

    def generate(self):
        """Generate the build system"""

        # Generate the Meson toolchain
        toolchain = MesonToolchain(self)
        toolchain.generate()

    def build(self):
        """Build this project"""

        meson = Meson(self)
        meson.configure()
        meson.build()
        meson.test()

    def package(self):
        """Install project headers"""

        meson = Meson(self)
        meson.install()

    def package_info(self):
        """Package information"""

        self.cpp_info.libs = [self.name]
        self.cpp_info.includedirs = ["include"]
