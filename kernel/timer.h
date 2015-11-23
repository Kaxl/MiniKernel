#ifndef _TIMER_H_
#define _TIMER_H_

#include "../common/types.h"

#define MAX_FREQ    1193180
#define MIN_FREQ    18.21
#define MAX_DIV     65535
#define MIN_DIV     1


/**
 * Timer structure to store the tick and the frequency
 */
typedef struct timer {
    uint32_t tick;
    uint32_t freq_hz;
} timer;

extern void timer_init(uint32_t freq_hz);
extern void timer_handler();
extern uint get_ticks();
extern void sleep(uint cs);

#endif
