from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import sys
import os
import subprocess
import platform

class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)

class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        
        # Ensure the extension ends up in the package directory
        package_dir = os.path.join(extdir, "toposolve")
        if not os.path.exists(package_dir):
            os.makedirs(package_dir)

        # Create build directory
        build_temp = os.path.join(self.build_temp, "build")
        if not os.path.exists(build_temp):
            os.makedirs(build_temp)

        # Ensure proper slashes for Windows
        package_dir = package_dir.replace("\\", "/")
        
        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={package_dir}",
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE={package_dir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            "-DCMAKE_BUILD_TYPE=Release"
        ]

        build_args = ["--config", "Release"]

        env = os.environ.copy()
        if platform.system() == "Windows":
            cmake_args += [f"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE={package_dir}"]
            build_args += ["--", "/m"]
        else:
            build_args += ["--", "-j2"]


        subprocess.check_call(
            ["cmake", ext.sourcedir] + cmake_args,
            cwd=build_temp,
            env=env
        )
        subprocess.check_call(
            ["cmake", "--build", "."] + build_args,
            cwd=build_temp,
            env=env
        )

        print(f"Built files in {package_dir}:")
        for root, dirs, files in os.walk(package_dir):
            for file in files:
                print(os.path.join(root, file))

setup(
    packages=["toposolve"],
    package_dir={"": "src"},
    ext_modules=[CMakeExtension("toposolve._toposolve")],
    cmdclass={"build_ext": CMakeBuild},
)