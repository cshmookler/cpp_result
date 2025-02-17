"""cpp_result test package Conan file"""

import os

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.meson import Meson, MesonToolchain


required_conan_version = ">=2.3.0"


class cpp_resultTestPackage(ConanFile):
    """cpp_result test package"""

    # Required
    name = "test_package"
    version = "1.0.0"

    # Configuration
    settings = "os", "compiler", "build_type", "arch"

    def build_requirements(self):
        """Declare dependencies of the build system"""

        self.tool_requires("meson/1.6.0")

    def requirements(self):
        """Declare library dependencies"""

        self.requires(self.tested_reference_str)

    def layout(self):
        """Set the layout of the build files"""

        self.folders.build = os.path.join(self.recipe_folder, "build")
        self.folders.generators = os.path.join(self.folders.build, "generators")

    def generate(self):
        """Generate the build system"""

        toolchain = MesonToolchain(self)
        toolchain.generate()

    def build(self):
        """Build the test project"""

        meson = Meson(self)
        meson.configure()
        meson.build()

    def test(self):
        """Execute the generated executable(s)"""

        if can_run(self):
            cmd = os.path.join(self.build_folder, "test_package")
            self.run(cmd, env="conanrun")
