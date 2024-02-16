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
    MG90S servo(15);
    servo.enable();

    GCodeParser gcodeParser;
    GCode gcode;

    int delay = 50;  // us
    int steps = 10000;

    // en, step, dir, ms1, ms2, diag
    TMC2209 driverX(20, 17, 16, 19, 18, 21);
    TMC2209 driverY(2, 5, 6, 3, 4, 7);
    driverX.enable();
    driverY.enable();


    Plotter plotter(servo, driverX, driverY);
    plotter.penUp();

    stdio_init_all();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(1000);
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(1000);
    }
    
    while (true) {
        if (!gcodeParser.getGCode(gcode)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');  
            std::cout << "Parsing error.\n";
            gcode.dump();
            continue;
        }

        if (gcode.type == 'M' && gcode.number == 99) {
            // std::cout << "Setting servo level to: " << (int)gcode.x << std::endl;
            servo.setLevel((int)gcode.x);
            std::cout << "OK\n";
        } else if (gcode.type == 'M' && gcode.number == 3) {
            plotter.penUp();
            sleep_ms(100);
            std::cout << "OK\n";
        } else if (gcode.type == 'M' && gcode.number == 4) {    
            plotter.penDown();
            sleep_ms(200);
            std::cout << "OK\n";
        } else if (gcode.type == 'G' && gcode.number == 0 || gcode.type == 'G' && gcode.number == 1) {
            plotter.move(gcode.x, gcode.y);
        } else if (gcode.type == 'G') {
            std::cout << "Turning motor 1 direction 1\n";
            driverX.turnSteps(steps, delay);
            sleep_ms(300);

            std::cout << "Turning motor 1 direction 2\n";
            driverX.turnSteps(-steps, delay);
            sleep_ms(300);

            std::cout << "Turning motor 2 direction 1\n";
            driverY.turnSteps(steps, delay);
            sleep_ms(300);

            std::cout << "Turning motor 2 direction 2\n";
            driverY.turnSteps(-steps, delay);
            sleep_ms(300);
        }
    }
}
