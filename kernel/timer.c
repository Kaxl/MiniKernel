#include "timer.h"
#include "controller.h"

// Timer properties
volatile timer t = {
    .tick = 0,
    .freq_hz = 0
};

void timer_init(uint32_t freq_hz) {
    uint16_t div = 0;
    // Check the frequency
    if (freq_hz < MIN_FREQ)
        div = MIN_DIV;
    else if (freq_hz > MAX_FREQ)
        div = MAX_DIV;
    else {
        div = MAX_FREQ / freq_hz;
    }

    // Programmation of PIT
    outb(0x43, 0x36);
    outb(0x40, div & 0xFF);
    outb(0x40, div >> 8);

    t.freq_hz = freq_hz;
}

void timer_handler() {
    // wait for tick
    t.tick++;
}

/**
 * @brief Get the number of tick since the system started.
 *
 * @return  The tick's number
 */
uint get_ticks() {
    return t.tick;
}

/**
 * @brief Wait for 'ms' milliseconds
 *
 * Calculate last tick of the sleep and wait while the current
 * tick has not reached it.
 *
 * @param ms Number of milliseconds to wait
 */
void sleep(uint ms) {
    uint32_t end = get_ticks() + (ms / 1000 * t.freq_hz);

    while (get_ticks() != end);
}


