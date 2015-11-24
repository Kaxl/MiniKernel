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

/**
 * @brief Initialization of timer
 *
 * @param freq_hz Frequency of the timer (~100hz on most system)
 */
extern void timer_init(uint32_t freq_hz);

/**
 * @brief Increment the timer value.
 *
 * Called by the timer interruption.
 */
extern void timer_handler();

/**
 * @brief Get the number of tick since the system started.
 *
 * @return  The tick's number
 */
extern uint get_ticks();

/**
 * @brief Wait for 'ms' milliseconds
 *
 * Calculate last tick of the sleep and wait while the current
 * tick has not reached it.
 *
 * @param ms Number of milliseconds to wait
 */
extern void sleep(uint ms);

#endif
