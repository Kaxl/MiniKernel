#include "keyboard.h"
#include "screen.h"
#include "controller.h"

#define SHIFT_CHARACTER 0x123
//int layout = LAYOUT_US;
int buffer[1024];
int i_read = 0;
int i_write = 0;

char us_layout[100] = "--1234567890-=--qwertyuiop[]--asdfghjkl;\,\,-<zxcvbnm,./-1234567";
char us_layout_shift[100] = "--1234567890-=--QWERTYUIOP[]--ASDFGHJKL;\,\,-<ZXCVBNM,./-1234567";

static shift = false;

void keyboard_init() {

}

void keyboard_handler() {
    int c = (int)(inb(0x60));
    if (!(c >> 7)) {    // If bit 8 is 0x0, the key is push
        i_write &= 1023;
        buffer[i_write++] = c;
    }
    else if (c == SHIFT_CHARACTER) {
        shift = true;
    }
}

int getc() {
    while ((i_read < i_write) || (i_read - i_write > 512)) {
        printf("%c", us_layout[buffer[i_read & 1023]]);
        i_read++;
    }
    return 0;
}
