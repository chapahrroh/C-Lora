cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()
add_executable(inverLora inverLora.cpp)
pico_enable_stdio_usb(inverLora 0)
pico_enable_stdio_uart(inverLora 1)
pico_add_extra_outputs(inverLora)
add_subdirectory(src)
target_link_libraries(inverLora pico_stdlib hardware_spi Loralib)


