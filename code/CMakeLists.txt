cmake_minimum_required(VERSION 3.20)

include(pico-sdk/pico_sdk_init.cmake)

project(xyplotter C CXX ASM)

pico_sdk_init()


add_subdirectory(lib)
add_subdirectory(test)


# add_executable(${PROJECT_NAME}
# 	main.c
# )

# target_link_libraries(${PROJECT_NAME}
# 	mechanical_dial_lib
# 	pico_stdlib
# 	hardware_adc
# )

# target_include_directories(${PROJECT_NAME} PUBLIC
# 	"${PROJECT_BINARY_DIR}"
# 	"${PROJECT_SOURCE_DIR}/lib"
# )
# pico_add_extra_outputs(${PROJECT_NAME})
