#include <stdio.h>
#include "pico/stdlib.h"
#include "mg90s.h"


void test_tristate(MG90S & servo)
{
    while(1) {
        printf("-90 deg\n");
        servo.setLevel(MG90S_PWM_LEVEL_MIN);
        sleep_ms(1000);
        printf("0 deg\n");
        servo.setLevel(MG90S_PWM_LEVEL_MID);
        sleep_ms(1000);
        printf("90 deg\n");
        servo.setLevel(MG90S_PWM_LEVEL_MAX);
        sleep_ms(1000);
    }
}

void test_range(MG90S & servo)
{
    for (uint i = MG90S_PWM_LEVEL_MIN; i < MG90S_PWM_LEVEL_MAX; i += 100) {
        printf("%d\n", i);
        servo.setLevel(i);
        sleep_ms(300);
    }
}

int main()
{
    stdio_init_all();
    MG90S servo(15);
    servo.enable();

    while(1) {
        test_range(servo);
    }
    // test_tristate(servo); 
}
