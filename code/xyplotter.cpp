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

void blink()
{
    for (int i = 0; i < 3; i++ ) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);  // initially disabled
        sleep_ms(300);
        gpio_put(PICO_DEFAULT_LED_PIN, false);  // initially disabled
        sleep_ms(300);
    }
}

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    blink();

    // Init servo
    MG90S servo(SERVO_PWM);
    servo.enable();

    // Init stepper drivers
    TMC2209 driver1(DRIVER_1_EN, DRIVER_1_STP, DRIVER_1_DIR, DRIVER_1_MS1, DRIVER_1_MS2, DRIVER_1_DIAG);
    TMC2209 driver2(DRIVER_2_EN, DRIVER_2_STP, DRIVER_2_DIR, DRIVER_2_MS1, DRIVER_2_MS2, DRIVER_2_DIAG);
    driver1.enable();
    driver2.enable();
//
//    driver1.turnSteps(5000, 100);
//    driver1.turnSteps(-5000, 100);
//    driver2.turnSteps(5000, 100);
//    driver2.turnSteps(-5000, 100);

    // Init plotter
    Plotter plotter(servo, driver1, driver2);
    plotter.penUp();

    // Init parser
    GCodeParser gcodeParser;

    stdio_init_all();
    while (true) {
        std::unique_ptr<AbstractGCode> gcode = gcodeParser.getGCode();
        if (gcode == nullptr) {
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "ERR" << std::endl;
            continue;
        }
        gcode->execute(&plotter);
//        std::cout << *gcode << std::endl;
        std::cout << "OK" << std::endl;
    }
}
