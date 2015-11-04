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
#include "../common/string.h"

// Screen properties
volatile screen s = {
    .cursor = (ushort *)FIRST_ADDR,
    .textColor = C_WHITE,
    .bgColor = C_BLACK
};


////////////////////////////////////////////////////////////////////////////////////////
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
    // Warning : it changes the current text color
    setTextColor(color);
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
    // Warning : it changes the current background color
    setBackgroundColor(color);
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

    // Check if character is /n, /r, ...
    switch (character) {
        case '\n':
            s.cursor += SCREEN_WIDTH;
            break;
        case '\r':
            s.cursor = (ushort *)((uint)(s.cursor) & ~(0xFF));
            break;
        default:
            // Reset char
            *s.cursor = 0x0;

            // Set the text and bg color
            *s.cursor = (s.bgColor << 12) | (s.textColor << 8);

            // Move the cursor
            // Set char (text and bg color and character value)
            *s.cursor = (s.bgColor << 12) | (s.textColor << 8) | character;
            s.cursor++;
            break;
    }

    // Shift the screen if cursor is bigger than the last address
    if (s.cursor > (ushort *)(LAST_ADDR)) {
        // Reset the cursor at the beginning of the line
        s.cursor -= SCREEN_WIDTH;
        // Each line is replaced by the next one (+SCREEN_WIDTH)
        // To remove the last line, we need to remove (SCREEN_WIDTH-1) * 2
        // because each char is coded on 16 bits
        for (ushort* i = (ushort *)FIRST_ADDR; i < (ushort *)(LAST_ADDR - ((SCREEN_WIDTH - 1) * 2)); i++) {
            *i = *(i + SCREEN_WIDTH);
        }
        // Clear the last line
        // Text and bg color are kept
        for (ushort* i = (ushort *)LAST_ADDR; i >= (ushort *)(LAST_ADDR - ((SCREEN_WIDTH - 1) * 2)); i--) {
            *i = 0x0;
            *i = (s.bgColor << 12) | (s.textColor << 8);
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
void printf(char *s, ...) {

    uint32_t* p = ((uint32_t*)&s);
    char string[128];   // Buffer to store the string during conversion
    p++;
    while (*s) {
        // If we have a '%', check the next char for the type and print the value
        if (strncmp(s, "%", 1) == 0) {
            s++; // Skip the %
            switch(*s) {
                // 4 bytes plus haut, l'argument suivant
                case 'c':
                    // character
                    printCharacter(*((char *)(p))); // Print the character value
                    break;
                case 's':
                    // string (array of character)
                    printString(*(char **)(p));     // Give string address
                    break;
                case 'd':
                    // integer
                    itoa(*((int *)(p)), string);    // Conversion to char array
                    printString(string);
                    break;
                case 'x':
                    // hexadecimal in lowercase
                    xtoa(*((int *)(p)), string);    // Conversion to hex string
                    printString(string);
                    break;
            }
            p++; // Next argument
        }
        else {
            printCharacter(*(s));
        }
        s++; // Next character
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
    int pos;
    int msb, lsb;
    outb(0x3d4, 0xE);
    msb = (ushort)(inb(0x3d5)); // MSB of pos
    outb(0x3d4, 0xF);
    lsb = (ushort)(inb(0x3d5)); // LSB of pos

    pos = lsb;
    pos = pos | (msb << 8);

    // Conversion in (x, y) coordinates
    *x = (uchar)(pos % SCREEN_WIDTH);
    *y = (uchar)(pos / SCREEN_WIDTH);
}

