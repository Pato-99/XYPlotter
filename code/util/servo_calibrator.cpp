/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

#include "mg90s.h"

// #define MG90S_PWM_LEVEL_MIN 1562
// #define MG90S_PWM_LEVEL_MID 4167
// #define MG90S_PWM_LEVEL_MAX 7812


MG90S servo(15);


void process_gcode(char * buffer)
{
    int n;
    if (sscanf(buffer, " g%d", &n) != 1) {
        printf("Wrong input.\n");
        return;
    }

    switch (n) {
        case 0:
        case 1:
            printf("move line\n");
            break;
        case 28:
            printf("homing\n");
            break;
        default:
            printf("not implemented\n");
            return;
    }
}

void process_mcode(char * buffer)
{
    int n;
    if (sscanf(buffer, " m%d", &n) != 1) {
        printf("Wrong input.\n");
        return;
    }
    switch (n) {
        case 0:
        case 1:
            printf("pause\n");
            break;
        case 2:
            printf("stop\n");
            break;
        case 3:
            printf("pen down\n");
            break;
        case 4:
            printf("pen up\n");
            break;
        case 18:
            printf("disable stepper motors\n");
            break;
        case 19:
            printf("enable stepper motors\n");
            break;
        case 99:
            int value;
            if (sscanf(buffer, " m99%d", &value) != 1)
                return;
            printf("Setting servo value to: %d\n", value);
            servo.setLevel(value);
            break;
        default:
            printf("not implemented\n");
            return;
    }
}



int main() {
    stdio_init_all();

    servo.enable();

    uint value = MG90S_PWM_LEVEL_MID;
    char ch;
    char buffer[128];
    while (true) {
        fgets(buffer, sizeof(buffer), stdin);

        // Determine GCode
        if (sscanf(buffer, " %c", &ch) != 1) {
            printf("Wrong input.\n");
            continue;
        }
        switch (ch) {
            case 'g':
                process_gcode(buffer);
                break;
            case 'm':
                process_mcode(buffer);
                break;
            default:
                printf("not implemented\n");
        }

            
        // if (value > MG90S_PWM_LEVEL_MAX || value < MG90S_PWM_LEVEL_MIN) {
        //     printf("Value out of range: %d\n", value);
        //     continue;
        // }

        // printf("Setting PWM value to: %d\n", value);
        // servo.setLevel(value);
    }
}
