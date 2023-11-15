#include <iostream>
#include "pico/stdlib.h"

#include "mg90s.h"
#include "gcode.h"

// #define MG90S_PWM_LEVEL_MIN 1562
// #define MG90S_PWM_LEVEL_MID 4167
// #define MG90S_PWM_LEVEL_MAX 7812


int main() {
    MG90S servo(15);
    servo.enable();

    GCodeParser gcodeParser;
    GCode gcode;

    stdio_init_all();
    
    while (true) {
        if (gcodeParser.getGCode(gcode) && gcode.type == 'M' && gcode.number == 99) {
            std::cout << "Setting servo level to: " << (int)gcode.x << std::endl;
            servo.setLevel((int)gcode.x);
        } else {
            std::cout << "Parsing error." << std::endl;
        }
    }
}
