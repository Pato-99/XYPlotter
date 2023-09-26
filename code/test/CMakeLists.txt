add_executable(test_mg90s test_mg90s.cpp)
target_link_libraries(test_mg90s mg90s)
target_include_directories(test_mg90s PUBLIC
	"${PROJECT_SOURCE_DIR}/lib"
)
pico_enable_stdio_usb(test_mg90s 1)
pico_enable_stdio_uart(test_mg90s 0)
pico_add_extra_outputs(test_mg90s)

add_executable(test_tmc test_tmc.cpp)
target_link_libraries(test_tmc pico_stdlib hardware_adc)
pico_add_extra_outputs(test_tmc)
