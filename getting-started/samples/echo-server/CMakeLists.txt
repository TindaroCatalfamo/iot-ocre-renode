cmake_minimum_required(VERSION 3.20.0)

# Set the WASI SDK toolchain file
set(CMAKE_TOOLCHAIN_FILE /opt/wasi-sdk/share/cmake/wasi-sdk-p1.cmake)
set(CMAKE_BUILD_TYPE Release)
set(APPNAME echo-server)
project(${APPNAME})

# Include the WAMR socket library CMake file (adjust path as needed)
include(../../external/wasm-micro-runtime/core/iwasm/libraries/lib-socket/lib_socket_wasi.cmake)

add_compile_options(
    -O0 -Wno-unknown-attributes
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-undefined -z stack-size=4096")
add_link_options(
    -Wl,--strip-all # Strip all symbol/debug information from the binary
)
add_executable(${APPNAME}.wasm main.c)

# Add socket support for WASM from IWASM
target_include_directories(${APPNAME}.wasm PRIVATE
    ../../external/wasm-micro-runtime/core/iwasm/libraries/lib-socket
)
target_link_libraries(${APPNAME}.wasm socket_wasi_ext)
