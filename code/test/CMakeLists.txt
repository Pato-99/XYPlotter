# TEST MG90S
add_executable(test_mg90s test_mg90s.cpp)
target_link_libraries(test_mg90s mg90s)
target_include_directories(test_mg90s PUBLIC
	"${PROJECT_SOURCE_DIR}/lib"
)
pico_enable_stdio_usb(test_mg90s 1)
pico_enable_stdio_uart(test_mg90s 0)
pico_add_extra_outputs(test_mg90s)


# TEST TMC2209
add_executable(test_tmc test_tmc.cpp)
target_link_libraries(test_tmc tmc2209)
target_include_directories(test_tmc PUBLIC
	"${PROJECT_SOURCE_DIR}/lib"
)
pico_enable_stdio_usb(test_tmc 1)
pico_enable_stdio_uart(test_tmc 1)
pico_add_extra_outputs(test_tmc)


# TEST GCODE
add_executable(test_gcode test_gcode.cpp)
target_link_libraries(test_gcode pico_stdlib gcode)
target_include_directories(test_gcode PUBLIC
	"${PROJECT_SOURCE_DIR}/lib"
)

pico_enable_stdio_usb(test_gcode 1)
pico_enable_stdio_uart(test_gcode 1)
pico_add_extra_outputs(test_gcode)
