cmake_minimum_required(VERSION 3.18)
project(toposolve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set architecture flags for Apple
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for macOS" FORCE)
endif()

# Add Python and pybind11
execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
find_package(pybind11 CONFIG REQUIRED PATHS "${pybind11_DIR}")

pybind11_add_module(_toposolve ${CMAKE_CURRENT_SOURCE_DIR}/src/toposolve/_toposolve.cpp)

# Ensure proper output directory structure for Windows
if(WIN32)
    set_target_properties(_toposolve PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/toposolve
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/toposolve
    )
endif()

# Set Mac-specific architecture
if(APPLE)
    set_target_properties(_toposolve PROPERTIES OSX_ARCHITECTURES "x86_64;arm64")
endif()
