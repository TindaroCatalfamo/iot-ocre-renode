cmake_minimum_required(VERSION 3.20.0)

# Set the WASI SDK toolchain file
set(CMAKE_TOOLCHAIN_FILE /opt/wasi-sdk/share/cmake/wasi-sdk-p1.cmake)

# Set the project name (needs to come after the toolchain file) 
set(APPNAME hello-world)
project(${APPNAME})

# Set the linker flags 
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--strip-all -Wl,--allow-undefined")

# Set compilation flags
add_compile_options(
    -O0 -Wno-unknown-attributes
    -O3
    -Wall
    -Wextra
    -Wno-unused-parameter
)

# Create the executable target
add_executable(${APPNAME}.wasm main.c)
