#include <iostream>
#include <cmath>
#include "pico/stdlib.h"
// #include "hardware/adc.h"


#include "tmc2209.h"

// bool motorControlCallback(struct repeating_timer * t)
// {
//     stepDelay = convert(adc_read());
//     if (stepDelay >= 1000) {
//         gpio_put(DIR_PIN_1, 1);
//         stepDelay = 2000 - stepDelay + 50; 
//     }
//     else {
//         gpio_put(DIR_PIN_1, 0);
//         stepDelay += 50;
//     }
//     std::cout << "Step delay: " << stepDelay << std::endl;
//     return true;
// }





struct Vec2D
{
    const double x;
    const double y;

    Vec2D(double x, double y)
        : x(x), y(y)
    {}

    /**
     * Perform a 45deg rotation. Return new Vec2D.
     * 
     * @param x
     * @param y
    */
    Vec2D rotate()
    {
        return Vec2D((x - y) / sqrt(2), (x + y) / sqrt(2));
    }

};


class Plotter
{
public:
    TMC2209 driverX;
    TMC2209 driverY;

private:
    Vec2D currentPos;
    int delay;  // speed

public:
    void moveTo(double x, double y);
};


int main()
{
    stdio_init_all();

    int delay = 25;  // us
    int steps = 20000;

    // en, step, dir, ms1, ms2, diag
    TMC2209 driverX(20, 17, 16, 19, 18, 21);
    TMC2209 driverY(2, 5, 6, 3, 4, 7);
    driverX.enable();
    driverY.enable();

    // driverX.setMicrostepping(MICROSTEPPING::MS8);
    // driverY.setMicrostepping(MICROSTEPPING::MS16);

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);


    gpio_init(0);
    gpio_set_dir(0, GPIO_IN);

    gpio_pull_down(0);


    // adc_init();
	// adc_gpio_init(26);
	// adc_select_input(0);

    // struct repeating_timer timer;
    // add_repeating_timer_ms(30, motorControlCallback, NULL, &timer);

    while(1) {
        if (gpio_get(0)) {
            gpio_put(PICO_DEFAULT_LED_PIN, 1);
        } else {
            gpio_put(PICO_DEFAULT_LED_PIN, 0);
        }

        std::cout << "Turning motor 1 direction 1\n";
        driverX.setDir(1);
        driverX.turnSteps(steps, delay);
        sleep_ms(300);

        std::cout << "Turning motor 1 direction 2\n";
        driverX.setDir(0);
        driverX.turnSteps(steps, delay);
        sleep_ms(300);

        std::cout << "Turning motor 2 direction 1\n";
        driverY.setDir(1);
        driverY.turnSteps(steps, delay);
        sleep_ms(300);

        std::cout << "Turning motor 2 direction 2\n";
        driverY.setDir(0);
        driverY.turnSteps(steps, delay);
        sleep_ms(300);
    }
}
