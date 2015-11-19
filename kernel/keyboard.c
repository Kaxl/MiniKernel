#include "keyboard.h"
#include "screen.h"
#include "controller.h"

//int layout = LAYOUT_US;
int buffer[1000];
int i_read = 0;
int i_write = 0;

char us_layout[100] = {'-',
    '-',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '-',
    '-',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '[',
    ']',
    '-',
    '-',
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    '\'',
    '\\',
    '-',
    '<',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    '-',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7'};

void keyboard_init() {
    
}

void keyboard_handler() {
    int c = (int)(inb(0x60));
    if ((c >> 7) == 0)
        buffer[i_write++] = c;

    getc();
}

int getc() {
    while (i_read < i_write) { 
        printf("%c", us_layout[buffer[i_read++]]);
    }
    return 0;
}
