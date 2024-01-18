cmake_minimum_required(VERSION 3.12)

add_library(Loralib Loralib.cpp Loralib.h)

target_link_libraries(Loralib pico_stdlib hardware_spi)

