#include <iostream>
#include <limits>
#include "pico/stdlib.h"

#include "mg90s.h"
#include "gcode.h"
#include "tmc2209.h"
#include "plotter.h"

// #define MG90S_PWM_LEVEL_MIN 1562
// #define MG90S_PWM_LEVEL_MID 4167
// #define MG90S_PWM_LEVEL_MAX 7812


int main() {
    MG90S servo(22);
    servo.enable();

    GCodeParser gcodeParser;

    int delay = 50;  // us
    int steps = 10000;

    // en, step, dir, ms1, ms2, diag
    TMC2209 driverX(4, 1, 0, 3, 2, 19);
    TMC2209 driverY(12, 7, 6, 11, 10, 20);
    driverX.enable();
    driverY.enable();


    Plotter plotter(servo, driverX, driverY);
    plotter.penUp();

    stdio_init_all();

    while (true) {
        std::cout << "GCode:" << std::endl;
        std::unique_ptr<GCode> gcode = gcodeParser.getGCode();
        if (gcode == nullptr) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  
            std::cout << "Parsing error.\n";
            continue;
        }
        gcode->execute(plotter);
    }
}
