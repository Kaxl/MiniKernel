#include "timer.h"
#include "controller.h"

// Timer properties
volatile timer t = {
    .tick = 0,
    .freq_hz = 0
};

void timer_init(uint32_t freq_hz) {

    uint16_t div = 0;
    if (freq_hz < MIN_FREQ)
        div = MIN_DIV;
    else if (freq_hz > MAX_FREQ)
        div = MAX_DIV;
    else {
        printf("Else : %d", freq_hz);
        //div = (int)(freq_hz * (MAX_DIV / MAX_FREQ));
        div = (uint16_t)(freq_hz * (65535 / 1193180));
        div = 55;
    }

    printf("Div : %d\r\n", div);

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

uint get_ticks() {
    return t.tick;
}

void sleep(uint cs) {
    uint32_t end = get_ticks() + (cs / 100 * t.freq_hz);

    while (get_ticks() < end);
}


