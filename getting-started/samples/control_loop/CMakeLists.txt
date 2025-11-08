cmake_minimum_required(VERSION 3.20.0)

# Set the WASI SDK toolchain file (contenitore dev: /opt/wasi-sdk)
set(CMAKE_TOOLCHAIN_FILE /opt/wasi-sdk/share/cmake/wasi-sdk-p1.cmake)

# Project name
set(APPNAME control_loop)
project(${APPNAME})

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--strip-all -Wl,--allow-undefined")

# Compile options
add_compile_options(
    -O3
    -Wall
    -Wextra
    -Wno-unused-parameter
)

# Create the executable target that will produce sensor_polling.wasm
add_executable(${APPNAME}.wasm main.c)

# Ensure the output goes to the build/ directory (this is standard CMake behaviour when you build in a build dir)
