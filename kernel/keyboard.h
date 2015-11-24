#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define SHIFT_LEFT  0x2A
#define SHIFT_RIGHT 0x36
#define CAPSLOCK    0x3A
#define RETURN      0x1C
#define BACKSPACE   0x0E
#define TAB         0x0F
#define ESC         0x01

#define LAYOUT_US 1
#define LAYOUT_CH 2

#define BUFFER_SIZE 1024

#include "../common/types.h"

/**
 * Circular buffer to store characters
 */
typedef struct buffer {
    uint32_t data[BUFFER_SIZE];
    uint32_t counter;
    uint32_t i_read;
    uint32_t i_write;
} buffer;

/**
 * @brief Initialisation of keyboard
 *
 * @param model layout for the initialization (US / CH)
 */
extern void keyboard_init(int model);

/**
 * @brief Keyboard handler
 *
 * Call when a keyboard interruption occurs
 */
extern void keyboard_handler();

/**
 * @brief Get a character from the buffer
 *
 * @return The character from the buffer,
 *         -1 if there is no character in the buffer
 */
extern int getc();

#endif
