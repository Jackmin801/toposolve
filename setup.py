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
        
        build_temp = os.path.join(self.build_temp, "build")
        if not os.path.exists(build_temp):
            os.makedirs(build_temp)

        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            "-DCMAKE_BUILD_TYPE=Release"
        ]

        build_args = ["--config", "Release"]

        env = os.environ.copy()
        if platform.system() == "Windows":
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

setup(
    name="toposolve",
    version="0.1.2",
    author="Jack Min Ong",
    author_email="ongjackm@gmail.com",
    description="A fast C++ implementation of the Held-Karp algorithm for solving TSP",
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    url="https://github.com/Jackmin801/toposolve",
    packages=["toposolve"],
    package_dir={"": "src"},
    ext_modules=[CMakeExtension("toposolve._toposolve")],  # Updated name here
    cmdclass={"build_ext": CMakeBuild},
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires=">=3.6",
    setup_requires=["pybind11>=2.6.0"],
    install_requires=["pybind11>=2.6.0"],
    zip_safe=False,
)