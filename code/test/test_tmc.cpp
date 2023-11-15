#include <iostream>
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


int main()
{
    stdio_init_all();

    int delay = 500;  // us
    int steps = 2000;
    TMC2209 driverX(2, 3, 4, 5, 6, 7);
    TMC2209 driverY(8, 9, 10, 11, 12, 13);
    driverX.enable();
    driverY.enable();


    // adc_init();
	// adc_gpio_init(26);
	// adc_select_input(0);

    // struct repeating_timer timer;
    // add_repeating_timer_ms(30, motorControlCallback, NULL, &timer);

    while(1) {
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
