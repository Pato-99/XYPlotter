
add_executable(servo_calibrator servo_calibrator.cpp)
target_link_libraries(servo_calibrator pico_stdlib)
target_link_libraries(servo_calibrator mg90s)
target_include_directories(servo_calibrator PUBLIC
	"${PROJECT_SOURCE_DIR}/lib"
)
pico_enable_stdio_usb(servo_calibrator 1)
pico_enable_stdio_uart(servo_calibrator 1)
pico_add_extra_outputs(servo_calibrator)
