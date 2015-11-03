/*
 * =====================================================================================
 *
 *       Filename:  screen.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:21:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "screen.h"
#include "base.h"
#include <stdarg.h>

// Screen properties
volatile screen s = {
    .cursor = (ushort *)FIRST_ADDR,
    .textColor = C_WHITE,
    .bgColor = C_BLACK
};

void initScreen() {
    // Default color
    setTextColor(C_WHITE);
    setBackgroundColor(C_BLACK);
    // Clear and set the cursor position
    clearScreen();

    // Change cursor
    // Cursor always visible
    outb(0x3d4, 0xA);
    outw(0x3d5, (int)inw(0x3d5) & ~(0x1 << 5));
    // Cursor fill
    outb(0x3d4, 0xA);
    outw(0x3d5, 0);
    outb(0x3d4, 0xB);
    outw(0x3d5, 0x1F);
}


////////////////////////////////////////////////////////////////////////////////////////
void clearScreen() {
    // Clear all the screen but keeps the text and background color,
    // only the character value is removed
    setCursorPosition(0, 0);
    for (ushort* i = (ushort *)FIRST_ADDR; i <= (ushort *)LAST_ADDR; i++) {
        *i = (s.bgColor << 12) | (s.textColor << 8) | 0x0;
    }
}


////////////////////////////////////////////////////////////////////////////////////////
void setAllTextColor(uchar color) {
    // Change text color of all screen
    // Warning : doesn't change the current text color
    for (ushort* i = (ushort *)FIRST_ADDR; i <= (ushort *)LAST_ADDR; i++) {
        *i = *i & ~(0xF00);
        *i = *i | (color << 8);
    }
}


////////////////////////////////////////////////////////////////////////////////////////
void setTextColor(uchar color) {
    s.textColor = color;
}


////////////////////////////////////////////////////////////////////////////////////////
uchar getTextColor() {
    return s.textColor;
}


////////////////////////////////////////////////////////////////////////////////////////
void setAllBackgroundColor(uchar color) {
    // Change background color of all screen
    // Warning : doesn't change the current background color
    for (ushort* i = (ushort *)FIRST_ADDR; i <= (ushort *)LAST_ADDR; i++) {
        *i = *i & ~(0xF000);
        *i = *i | (color << 12);
    }
}


////////////////////////////////////////////////////////////////////////////////////////
void setBackgroundColor(uchar color) {
    s.bgColor = color;
}


////////////////////////////////////////////////////////////////////////////////////////
uchar getBackgroundColor() {
    return s.bgColor;
}


////////////////////////////////////////////////////////////////////////////////////////
void printCharacter(char character) {
    // Reset char
    *s.cursor = 0x0;

    // Set char (text and bg color and character value)
    *s.cursor = (s.bgColor << 12) | (s.textColor << 8) | character;
    // Move the cursor
    s.cursor++;

    // Shift the screen if cursor is bigger than the last address
    if (s.cursor > (ushort *)(LAST_ADDR)) {
        // Reset the cursor at the beginning of the line
        s.cursor -= SCREEN_WIDTH;
        // Each line is replaced by the next one
        for (ushort* i = (ushort *)FIRST_ADDR; i < (ushort *)(LAST_ADDR - SCREEN_WIDTH); i++) {
            *i = *(i + SCREEN_WIDTH);
        }
        // Clear the last line
        // Text and bg color are kept
        for (ushort* i = (ushort *)LAST_ADDR; i >= (ushort *)(LAST_ADDR - SCREEN_WIDTH); i--) {
            *i = (s.bgColor << 12) | (s.textColor << 8) | 0x0;
        }
    }

    // Update the cursor position on the screen
    uchar x, y;
    x = (uchar)((((uint)s.cursor - FIRST_ADDR) / 2) % SCREEN_WIDTH);
    y = (uchar)((((uint)s.cursor - FIRST_ADDR) / 2) / SCREEN_WIDTH);
    setCursorPosition(x, y);
}


////////////////////////////////////////////////////////////////////////////////////////
void printString(char* string) {
    // Print character until 0 is reached
    while (*string) {
        printCharacter(*(string++));
    }
}


////////////////////////////////////////////////////////////////////////////////////////
void printf(const char *s, ...) {

    while (*s) {
        // If we have a '%', check the next char for the type and print the value
        if (strncmp(s, "%", 1) == 0) {
            s++; // Skip the %
            switch(*s) {
                // 4 bytes plus haut, l'argument suivant
                case 'c':
                    // character
                    //ch = va_arg(args, char);
                    printCharacter('a');
                    break;
                case 's':
                    // string (array of character)
                    break;
                case 'd':
                    // integer
                    break;
                case 'x':
                    // hexadecimal in lowercase
                    break;
            }
            s++; // Skip the type
        }
        else {
            printCharacter(*(s++));
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////
void setCursorPosition(uchar x, uchar y) {
    ushort pos = y * SCREEN_WIDTH + x;

    outb(0x3d4, 0xE);
    outw(0x3d5, (ushort)(pos >> 8));    // MSB of pos
    outb(0x3d4, 0xF);
    outw(0x3d5, (ushort)(pos & 0xFF));  // LSB of pos

    s.cursor = (ushort *)FIRST_ADDR;    // Go to first address
    s.cursor += (ushort)pos;            // Add the pos
}


////////////////////////////////////////////////////////////////////////////////////////
void getCursorPosition(uchar* x, uchar* y) {
    int pos, msb, lsb;
    outb(0x3d4, 0xE);
    msb = (int)(inw(0x3d5)); // MSB of pos
    outb(0x3d4, 0xF);
    lsb = (int)(inw(0x3d5)); // LSB of pos

    pos = lsb;
    pos = pos | (msb << 8);

    lineToGrid(pos, x, y);
}

////////////////////////////////////////////////////////////////////////////////////////
// NOT USED
ushort gridToLine(uchar x, uchar y) {
    // We need to multiply by 2 because each character is on 2 bytes
    return y * SCREEN_WIDTH + x;
}


////////////////////////////////////////////////////////////////////////////////////////
void lineToGrid(ushort pos, uchar* x, uchar* y) {
    // x is the division, y the modulo
    *x = (uchar)(((pos) - FIRST_ADDR) / SCREEN_WIDTH);
    *y = (uchar)(((pos) - FIRST_ADDR) % SCREEN_WIDTH);
}

////////////////////////////////////////////////////////////////////////////////////////
void itoa(int n, char* s) {
    char* p = s;
    char const digit = "0123456789";

    // Number is negative so we have to print a '-' before
    if (n < 0) *(p++) = '-';

    // Save the size of the array
    int tmp_n = n;
    while (tmp_n) {
        tmp_n = tmp_n / 10;
        p++;
    }
    
    // Write the integer from the back
    tmp_n = n;
    while (tmp_n) {
        *(p--) = digit[tmp_n%10];
        tmp_n = tmp_n / 10;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void xtoa(int n, char* s) {
    char* p = s;
    char const hexa = "0123456789ABCDEF";
   
    // Number is negative so we have to print a '-' before
    if (n < 0) *(p++) = '-';

    // As n is a hex number, we have to print '0x' before
    *(p++) = '0';
    *(p++) = 'x';

    // Save the size of the array
    int tmp_n = n;
    while (tmp_n > 15) {
        tmp_n = tmp_n / 16;
        p++;
    }

    // Write the hex from the back
    tmp_n = n;
    while (tmp_n > 15) {
        *(p--) = hex[tmp_n%16];
        tmp_n = tmp_n / 16;
    }
}
