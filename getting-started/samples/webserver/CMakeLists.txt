cmake_minimum_required(VERSION 3.20.0)

# Set the WASI SDK toolchain file
set(CMAKE_TOOLCHAIN_FILE /opt/wasi-sdk/share/cmake/wasi-sdk-p1.cmake)

# Set APPNAME and project name
set(APPNAME webserver)
project(${APPNAME})

# Include the WAMR socket library CMake file (adjust path as needed)
include(../../external/wasm-micro-runtime/core/iwasm/libraries/lib-socket/lib_socket_wasi.cmake)

# Set compilation flags
add_compile_options(
    -O0 -Wno-unknown-attributes
    -O3
    -Wall
    -Wextra
    -Wno-unused-parameter
)

# Set linker flags
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--strip-all -Wl,--allow-undefined")

# Add link options to strip all symbols and debug information
add_link_options(
    -Wl,--strip-all # Strip all symbol/debug information from the binary
)

# Collect the mongoose source files
file(GLOB mongoose ./src/mongoose.c)

# Add the executable target for the web server
add_executable(${APPNAME}.wasm src/main.c ${mongoose} src/inet_addr_shim.c)

# Add socket support for WASM from IWASM
target_include_directories(${APPNAME}.wasm PRIVATE
    ../../external/wasm-micro-runtime/core/iwasm/libraries/lib-socket/inc
)

# Link the WAMR socket library
target_link_libraries(${APPNAME}.wasm socket_wasi_ext)
