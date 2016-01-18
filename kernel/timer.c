#include "timer.h"
#include "controller.h"
#include "screen.h"

// Timer properties
volatile timer t = {
    .tick = 0,
    .freq_hz = 0
};

////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////
void timer_handler() {
    // wait for tick
    t.tick++;
    int* p = (int *)0x810000;
    if (*p == 0x1234)
        printf("Victory\n");
    printf("%d\n", *p);
}

////////////////////////////////////////////////////////////////////////////////////////
uint get_ticks() {
    return t.tick;
}

////////////////////////////////////////////////////////////////////////////////////////
void sleep(uint ms) {
    uint32_t end = get_ticks() + (ms / 1000 * t.freq_hz);

    while (get_ticks() != end);
}

