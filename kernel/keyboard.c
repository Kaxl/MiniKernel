#include "keyboard.h"
#include "screen.h"
#include "controller.h"

#define SHIFT_LEFT  0x2A
#define SHIFT_RIGHT 0x36
#define CAPSLOCK    0x3A
#define RETURN      0x1C
#define BACKSPACE   0x0E
#define TAB         0x0F
#define ESC         0x01

//int layout = LAYOUT_US;
char buffer[1024];
int i_read = 0;
int i_write = 0;

char us_layout[100] =       "--1234567890-=--qwertyuiop[]--asdfghjkl;'`,\\zxcvbnm,./-12 456789abcdefghijklknopqrtuwv<zy";
char us_layout_shift[100] = "--!@#$%^&*()_+--QWERTYUIOP{}--ASDFGHJKL:\"~,|ZXCVBNM<>?-12 4567------------------------>--";

static shift = false;
static capslock = false;

void keyboard_init() {

}

void keyboard_handler() {
    int c = (int)(inb(0x60));
    // Check if buffer is full
    if (i_read - i_write == 0) {
        int color = getTextColor();
        setTextColor(C_RED);
        printf("Error with keyboard : Buffer is full.\r\n");
        setTextColor(color);    // Restaure previous color
        return;
    }
    // Push key
    if (!(c >> 7)) {    // If bit 8 is 0x0, the key is push
        switch (c) {
            case SHIFT_LEFT:
            case SHIFT_RIGHT:
                shift = true;
                break;
            case CAPSLOCK:
                capslock = ~capslock;
                break;
            case RETURN:
                printf("\r\n");
                break;
            case BACKSPACE:
                // todo
                break;
            case ESC:
                // Exit insert mode
                break;
            case TAB:
                printf("\t");
                break;
            default:    // Any other key
                i_write &= 1023;
                if ((shift || capslock) && !(shift && capslock)) {
                    buffer[i_write] = us_layout_shift[c];
                }
                else {
                    buffer[i_write] = us_layout[c];
                }
                i_write++;
                break;

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
