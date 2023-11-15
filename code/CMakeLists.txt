cmake_minimum_required(VERSION 3.20)

include(pico-sdk/pico_sdk_init.cmake)

project(xyplotter C CXX ASM)

pico_sdk_init()


add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(util)
