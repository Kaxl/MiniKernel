#include "keyboard.h"
#include "screen.h"
#include "controller.h"

#define SHIFT_LEFT  0x2A
#define SHIFT_RIGHT 0x36
//int layout = LAYOUT_US;
char buffer[1024];
int i_read = 0;
int i_write = 0;

char us_layout[100] =       "--1234567890-=--qwertyuiop[]--asdfghjkl;\,\,-<zxcvbnm,./-12 4567";
char us_layout_shift[100] = "--1234567890-=--QWERTYUIOP[]--ASDFGHJKL;\,\,-<ZXCVBNM,./-12 4567";

static shift = false;

void keyboard_init() {

}

void keyboard_handler() {
    int c = (int)(inb(0x60));
    // Push key
    if (!(c >> 7)) {    // If bit 8 is 0x0, the key is push
        if (c == SHIFT_LEFT || c == SHIFT_RIGHT) {  // Shift key
            shift = true;
        }
        else {  // Any other key
            i_write &= 1023;
            if (shift) {
                buffer[i_write] = us_layout_shift[c];
            }
            else {
                buffer[i_write] = us_layout[c];
            }
            i_write++;
        }
    }
    else  {     // Else, the key is released
        c &= ~(0x1 << 7);   // Set the bit 8 to 0x0 to get the caracter value
        if (c  == SHIFT_LEFT || c == SHIFT_RIGHT) {  // Shift key
            shift = false;
        }
    }
}

int getc() {
    while ((i_read < i_write) || (i_read - i_write > 512)) {
        i_read &= 1023;
        printf("%c", buffer[i_read++]);
    }
    return 0;
}
