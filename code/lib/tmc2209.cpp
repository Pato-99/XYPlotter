#include "pico/stdlib.h"

#include "tmc2209.h"


TMC2209::TMC2209(uint en, uint stp, uint dir, uint ms1, uint ms2, uint diag)
    : en(en), stp(stp), dir(dir), ms1(ms1), ms2(ms2), diag(diag)
{
    gpio_init(en);
    gpio_set_dir(en, GPIO_OUT);
    gpio_put(en, 1);  // initially disabled

    gpio_init(stp);
    gpio_set_dir(stp, GPIO_OUT);

    gpio_init(dir);
    gpio_set_dir(dir, GPIO_OUT);

    // Default microstepping 1/64
    gpio_init(ms1);
    gpio_set_dir(ms1, GPIO_OUT);
    gpio_put(ms1, 1);

    gpio_init(ms2);
    gpio_set_dir(ms2, GPIO_OUT);
    gpio_put(ms2, 0);

    // Stall detection
    gpio_init(diag);
    gpio_set_dir(diag, GPIO_IN);
}

/**
 * Enable the driver. Pull EN pin low.
*/
void TMC2209::enable()
{
    gpio_put(this->en, 0);
}

/**
 * Disable the driver. Pull EN pin high.
*/
void TMC2209::disable()
{
    gpio_put(this->en, 1);
}

/**
 * Set direction. Pull DIR pin high or low.
*/
void TMC2209::setDir(bool dir)
{
    gpio_put(this->dir, dir);
}

/**
 * Do one step. Toggle STEP pin state.
*/
void TMC2209::step()
{
    gpio_put(this->stp, !gpio_get(this->stp));
}

/**
 * Turn n steps at fixed inter-step delay (speed).
 * 
 * @param n     number of steps
 * @param delay inter-step delay in microseconds
*/
void TMC2209::turnSteps(int n, int delay)
{
    for (int i = 0; i < n; i++) {
        this->step();
        sleep_us(delay);
    }
}

/**
 * Set microstepping.
 * MS1/MS2: 00/8, 01/64, 10/32, 11/16
*/
void TMC2209::setMicrostepping(MICROSTEPPING ms)
{
    switch (ms) {
        case MICROSTEPPING::MS8:
            gpio_put(this->ms1, 0);
            gpio_put(this->ms2, 0);
            break;
        case MICROSTEPPING::MS16:
            gpio_put(this->ms1, 1);
            gpio_put(this->ms2, 1);
            break;
        case MICROSTEPPING::MS32:
            gpio_put(this->ms1, 1);
            gpio_put(this->ms2, 0);
            break;
        case MICROSTEPPING::MS64:
            gpio_put(this->ms1, 0);
            gpio_put(this->ms2, 1);
            break;
    }
}
