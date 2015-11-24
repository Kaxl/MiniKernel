#include "keyboard.h"
#include "screen.h"
#include "../common/types.h"
#include "controller.h"

#define SHIFT_LEFT  0x2A
#define SHIFT_RIGHT 0x36
#define CAPSLOCK    0x3A
#define RETURN      0x1C
#define BACKSPACE   0x0E
#define TAB         0x0F
#define ESC         0x01

//#define BUFFER_SIZE 1024    // Must be a power of 2
#define BUFFER_SIZE 16    // Must be a power of 2

//int layout = LAYOUT_US;
char buffer[BUFFER_SIZE];
int i_read = 0;
int i_write = 0;

char us_layout[100] =       "--1234567890-=--qwertyuiop[]--asdfghjkl;'`,\\zxcvbnm,./-12 456789abcdefghijklknopqrtuwv<zy";
char us_layout_shift[100] = "--!@#$%^&*()_+--QWERTYUIOP{}--ASDFGHJKL:\"~,|ZXCVBNM<>?-12 4567------------------------>--";
char ch_layout[100] =       "--1234567890'^--qwertzuiope---asdfghjklea-,\\yxcvbnm,.--12 456789abcdefghijklknopqrtuwv<yz";
char ch_layout_shift[100] = "--+\"*c%&/()=?`--QWERTZUIOPu!--ASDFGHJKLeo-LYXCVBNM;:_-12 4567------------------------>--";
char* layout = ch_layout;
char* layout_shift = ch_layout_shift;
// £ç

static int shift = false;
static int capslock = false;

void keyboard_init() {

}

void keyboard_handler() {
    int c = (int)(inb(0x60));
    // Check if buffer is full
    int n = 0;
    if (i_write != i_read)
        n = i_write > i_read ? i_write - i_read : i_write + BUFFER_SIZE - i_read;

    if (n > BUFFER_SIZE - 1) {
        int color = getTextColor();
        setTextColor(C_RED);
        printf("Error with keyboard : Buffer is full.\r\n");
        printf("iread : %d\n\r", i_read);
        printf("iwrite : %d\n\r", i_write);
        printf("iread : %d / iwrite : %d\n\r", i_read, i_write);
        setTextColor(color);    // Restaure previous color
        return;
    }
    // Push key
    if (!(c >> 7)) {    // If bit 8 is 0x0, the key is push
        switch (c) {
            case SHIFT_LEFT:
            case SHIFT_RIGHT:
                shift = 1;
                break;
            case CAPSLOCK:
                capslock = ~capslock;
                break;
            case RETURN:
                printf("\r\n");
                break;
            case BACKSPACE:
                // In screen.c, \b is process to remove the character and set the cursor
                printf("\b");
                break;
            case ESC:
                // Exit insert mode
                break;
            case TAB:
                printf("\t");
                break;
            default:    // Any other key
                i_write &= (BUFFER_SIZE - 1);
                if ((shift || capslock) && !(shift && capslock)) {
                    buffer[i_write] = layout_shift[c];
                }
                else {
                    buffer[i_write] = layout[c];
                }
                i_write++;
                break;
        }
    }
    else  {     // Else, the key is released
        c &= ~(0x1 << 7);   // Set the bit 8 to 0x0 to get the caracter value
        if (c  == SHIFT_LEFT || c == SHIFT_RIGHT) {  // Shift key
            shift = 0;
        }
    }
}

int getc() {
    if ((i_read < i_write) || (i_read - i_write > 512)) {
        i_read &= (BUFFER_SIZE - 1);
        return buffer[i_read++];
    }
    return -1;
}
