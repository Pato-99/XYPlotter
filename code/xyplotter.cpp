#include <iostream>
#include <limits>
#include "pico/stdlib.h"

#include "mg90s.h"
#include "gcode.h"
#include "tmc2209.h"
#include "plotter.h"
#include "gcode_parser.h"

// CONFIG

#define SERVO_PWM 22

#define DRIVER_1_EN 4
#define DRIVER_1_STP 1
#define DRIVER_1_DIR 0
#define DRIVER_1_MS1 3
#define DRIVER_1_MS2 2
#define DRIVER_1_DIAG 19

#define DRIVER_2_EN 12
#define DRIVER_2_STP 7
#define DRIVER_2_DIR 6
#define DRIVER_2_MS1 11
#define DRIVER_2_MS2 10
#define DRIVER_2_DIAG 20

// #define MG90S_PWM_LEVEL_MIN 1562
// #define MG90S_PWM_LEVEL_MID 4167
// #define MG90S_PWM_LEVEL_MAX 7812


int main() {
    MG90S servo(SERVO_PWM);
    servo.enable();

    GCodeParser gcodeParser;

    TMC2209 driver1(DRIVER_1_EN, DRIVER_1_STP, DRIVER_1_DIR, DRIVER_1_MS1, DRIVER_1_MS2, DRIVER_1_DIAG);
    TMC2209 driver2(DRIVER_2_EN, DRIVER_2_STP, DRIVER_2_DIR, DRIVER_2_MS1, DRIVER_2_MS2, DRIVER_2_DIAG);
    driver1.enable();
    driver2.enable();


    Plotter plotter(servo, driver1, driver2);
    plotter.penUp();

    stdio_init_all();

    while (true) {
        std::unique_ptr<GCode> gcode = gcodeParser.getGCode();
        if (gcode == nullptr) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  
            std::cout << "Parsing error.\n";
            continue;
        }
        gcode->execute(&plotter);
    }
}
