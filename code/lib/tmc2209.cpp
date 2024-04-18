#include "pico/stdlib.h"

#include <iostream>

#include "tmc2209.h"


static char event_str[128];

static const char *gpio_irq_str[] = {
        "LEVEL_LOW",  // 0x1
        "LEVEL_HIGH", // 0x2
        "EDGE_FALL",  // 0x4
        "EDGE_RISE"   // 0x8
};

void gpio_event_string(char *buf, uint32_t events) {
    for (uint i = 0; i < 4; i++) {
        uint mask = (1 << i);
        if (events & mask) {
            // Copy this event string into the user string
            const char *event_str = gpio_irq_str[i];
            while (*event_str != '\0') {
                *buf++ = *event_str++;
            }
            events &= ~mask;

            // If more events add ", "
            if (events) {
                *buf++ = ',';
                *buf++ = ' ';
            }
        }
    }
    *buf++ = '\0';
}

void diag_callback(uint gpio, uint32_t events)
{
    gpio_event_string(event_str, events);
    std::cout << "GPIO " << gpio << " " << event_str << std::endl;
}


TMC2209::TMC2209(uint en, uint stp, uint dir, uint ms1, uint ms2, uint diag)
    : en(en), stp(stp), dir(dir), ms1(ms1), ms2(ms2), diag(diag)
{
    gpio_init(en);
    gpio_set_dir(en, GPIO_OUT);
    gpio_put(en, true);  // initially disabled

    gpio_init(stp);
    gpio_set_dir(stp, GPIO_OUT);

    gpio_init(dir);
    gpio_set_dir(dir, GPIO_OUT);

    // Default microstepping 1/64
    gpio_init(ms1);
    gpio_set_dir(ms1, GPIO_OUT);
    gpio_put(ms1, true);

    gpio_init(ms2);
    gpio_set_dir(ms2, GPIO_OUT);
    gpio_put(ms2, false);

    // Stall detection
    gpio_init(diag);
    gpio_set_dir(diag, GPIO_IN);
    gpio_set_irq_enabled_with_callback(diag, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &diag_callback);
}

/**
 * Enable the driver. Pull EN pin low.
*/
void TMC2209::enable() const
{
    gpio_put(this->en, false);
}

/**
 * Disable the driver. Pull EN pin high.
*/
void TMC2209::disable() const
{
    gpio_put(this->en, true);
}

/**
 * Set direction. Pull DIR pin high or low.
*/
void TMC2209::setDir(bool dir) const
{
    gpio_put(this->dir, dir);
}

/**
 * Do one step. Toggle STEP pin state.
*/
void TMC2209::step() const
{
    gpio_put(this->stp, !gpio_get(this->stp));
}

/**
 * Turn n steps at fixed inter-step delay (speed).
 * 
 * @param n     number of steps
 * @param delay inter-step delay in microseconds
*/
void TMC2209::turnSteps(int n, int delay) const
{
    if (n >= 0) {
        this->setDir(true);
    } else {
        this->setDir(false);
        n *= -1;
    }
    for (int i = 0; i < n; i++) {
        this->step();
        sleep_us(delay);
    }
}

/**
 * Set microstepping.
 * MS1/MS2: 00/8, 01/64, 10/32, 11/16
*/
void TMC2209::setMicrostepping(MICROSTEPPING ms) const
{
    switch (ms) {
        case MICROSTEPPING::MS8:
            gpio_put(this->ms1, false);
            gpio_put(this->ms2, false);
            break;
        case MICROSTEPPING::MS16:
            gpio_put(this->ms1, true);
            gpio_put(this->ms2, true);
            break;
        case MICROSTEPPING::MS32:
            gpio_put(this->ms1, true);
            gpio_put(this->ms2, false);
            break;
        case MICROSTEPPING::MS64:
            gpio_put(this->ms1, false);
            gpio_put(this->ms2, true);
            break;
    }
}
