#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define DIR_PIN 16
#define STEP_PIN 17
#define DELAY_US 100

int stepDelay = 500;  // us 

uint32_t convert(uint32_t raw)
{
	// 0 - (1 << 16) -> -10000 - 10000
	uint32_t res = raw * 2000;
	res = res / (1 << 12);
	return res;  // 0 - 2000
}

bool motorControlCallback(struct repeating_timer * t)
{
    stepDelay = convert(adc_read());
    if (stepDelay >= 1000) {
        gpio_put(DIR_PIN, 1);
        stepDelay = 2000 - stepDelay + 50;
    }
    else {
        gpio_put(DIR_PIN, 0);
        stepDelay += 50;
    }
    printf("Step delay: %d\n", stepDelay);
    return true;
}


int main()
{
    stdio_init_all();

    gpio_init(STEP_PIN);
    gpio_set_dir(STEP_PIN, GPIO_OUT);
    gpio_init(DIR_PIN);
    gpio_set_dir(DIR_PIN, GPIO_OUT);


    // adc_init();
	// adc_gpio_init(26);
	// adc_select_input(0);

    // struct repeating_timer timer;
    // add_repeating_timer_ms(30, motorControlCallback, NULL, &timer);


    // while (1) {
    //     gpio_put(STEP_PIN, 1);
    //     sleep_us(stepDelay);
    //     gpio_put(STEP_PIN, 0);
    //     sleep_us(stepDelay);
    // }

    while(1) {
        printf("Turning direction 1\n");
        gpio_put(DIR_PIN, 1);
        for (int i = 0; i < 30000; i++) {
            gpio_put(STEP_PIN, 1);
            sleep_us(stepDelay);
            gpio_put(STEP_PIN, 0);
            sleep_us(stepDelay);
        }
        sleep_ms(300);
        printf("Turning direction 2\n");
        gpio_put(DIR_PIN, 0);
        for (int i = 0; i < 30000; i++) {
            gpio_put(STEP_PIN, 1);
            sleep_us(stepDelay);
            gpio_put(STEP_PIN, 0);
            sleep_us(stepDelay);
        }
        sleep_ms(300);
    }
}
