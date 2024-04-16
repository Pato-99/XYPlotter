add_library(xyplotter
		gcode.cpp
		mg90s.cpp
		plotter.cpp
		tmc2209.cpp
		line.cpp
		plotter_gcodes.cpp
		gcode_parser.cpp
)

target_link_libraries(xyplotter
		pico_stdlib
		hardware_pwm
)

#
#add_library(tmc2209
#	tmc2209.cpp
#)
#target_link_libraries(tmc2209
#	pico_stdlib
#)
#
#
#add_library(mg90s
#	mg90s.cpp
#)
#
#target_link_libraries(mg90s
#	pico_stdlib
#	hardware_pwm
#)
#
#add_library(gcode
#	gcode.cpp
#)
#
#add_library(plotter
#	plotter.cpp
#)
#
#target_link_libraries(plotter
#	pico_stdlib
#)
