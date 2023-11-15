add_library(tmc2209
	tmc2209.cpp
)


add_library(mg90s
	mg90s.cpp
)

target_link_libraries(mg90s
	pico_stdlib
	hardware_pwm
)

add_library(gcode
	gcode.cpp
)
