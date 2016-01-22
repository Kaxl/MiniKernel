#include "keyboard.h"
#include "colors.h"
#include "screen.h"
#include "controller.h"

// Buffer
volatile buffer b = {
    .data = {},
    .counter = 0,
    .i_read = 0,
    .i_write = 0
};

// Characters of layouts (US / CH)
char us_layout[128] =       "--1234567890-=--qwertyuiop[]--asdfghjkl;'`,\\zxcvbnm,./-12 456789abcdefghijklknopqrtuwv<zy";
char us_layout_shift[128] = "--!@#$%^&*()_+--QWERTYUIOP{}--ASDFGHJKL:\"~,|ZXCVBNM<>?-12 4567------------------------>--";
char ch_layout[128] =       "--1234567890'^--qwertzuiope---asdfghjklea-,\\yxcvbnm,.--12 456789abcdefghijklknopqrtuwv<yz";
char ch_layout_shift[128] = "--+\"*c%&/()=?`--QWERTZUIOPu!--ASDFGHJKLea-L<YXCVBNM;:_-12 4567------------------------>--";
char* layout;
char* layout_shift;

static int shift = false;
static int capslock = false;

////////////////////////////////////////////////////////////////////////////////////////
void keyboard_init(int model) {
    if (model == LAYOUT_US) {
        layout = us_layout;
        layout_shift = us_layout_shift;
    }
    else {
        layout = ch_layout;
        layout_shift = ch_layout_shift;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void keyboard_handler() {
    int c = (int)(inb(0x60));
    // Check if buffer is full
    if (b.counter > BUFFER_SIZE - 1) {
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
                shift++;
                break;
            case CAPSLOCK:
                capslock = ~capslock;
                break;
            case RETURN:
                printf("\r\n");
                // Writes the character in the buffer
                b.i_write &= (BUFFER_SIZE - 1);
                b.data[b.i_write] = '\n';
                b.i_write++;
                b.counter++;
                break;
            case BACKSPACE:
                // In screen.c, \b is process to remove the character and set the cursor
                printf("\b");
                b.i_write &= (BUFFER_SIZE - 1);
                b.data[b.i_write] = '\b';
                b.i_write++;
                b.counter++;
                break;
            case ESC:
                // Exit insert mode
                break;
            case TAB:
                printf("\t");
                b.i_write &= (BUFFER_SIZE - 1);
                b.data[b.i_write] = '\t';
                b.i_write++;
                b.counter++;
                break;
            default:    // Any other key
                // Writes the character in the buffer
                b.i_write &= (BUFFER_SIZE - 1);
                if ((shift || capslock) && !(shift && capslock)) {
                    b.data[b.i_write] = layout_shift[c];
                }
                else {
                    b.data[b.i_write] = layout[c];
                }
                b.i_write++;
                b.counter++;
                break;
        }
    }
    else  {     // Else, the key is released
        c &= ~(0x1 << 7);   // Set the bit 8 to 0x0 to get the caracter value
        if (c  == SHIFT_LEFT || c == SHIFT_RIGHT) {  // Shift key
            shift--;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
int getc() {
    // Read a character from the buffer if not empty
    if (b.counter > 0) {
        b.i_read &= (BUFFER_SIZE - 1);
        b.counter--;
        return b.data[b.i_read++];
    }
    return -1;
}
