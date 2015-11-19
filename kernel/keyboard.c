#include "keyboard.h"
#include "screen.h"
#include "controller.h"

void keyboard_init() {

}

void keyboard_handler() {
    int c = (int)(inb(0x60));
    if ((c >> 7) == 0)
        printf("%x ", c);
}

int getc() {

}
