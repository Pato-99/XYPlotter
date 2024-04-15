cmake_minimum_required(VERSION 3.20)

include(pico-sdk/pico_sdk_init.cmake)

project(xyplotter C CXX ASM)

pico_sdk_init()

add_subdirectory(lib)
add_subdirectory(test)

add_executable(xyplotter_firmware ../xyplotter.cpp)
target_link_libraries(xyplotter_firmware pico_stdlib xyplotter)
target_include_directories(xyplotter_firmware PUBLIC
        "${PROJECT_SOURCE_DIR}/lib"
)
pico_enable_stdio_usb(xyplotter_firmware 1)
pico_enable_stdio_uart(xyplotter_firmware 1)
pico_add_extra_outputs(xyplotter_firmware)
