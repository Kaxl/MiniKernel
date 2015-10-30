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
}


////////////////////////////////////////////////////////////////////////////////////////
void clearScreen() {
    // Clear all the screen
    setCursorPosition(0, 0);
    for (ushort* i = (ushort *)FIRST_ADDR; i <= (ushort *)LAST_ADDR; i++) {
        //*i = 0x0;
        *i = (15 << 8) | 65;
    }
}


////////////////////////////////////////////////////////////////////////////////////////
void setAllTextColor(uchar color) {
    // Change text color of all screen
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            //setTextColor(i, j, color);
        }
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
// TODO
void setAllBackgroundColor(uchar color) {
    // Change background color of all screen
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            //setBackgroundColor(i, j, color);
        }
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
void printCharacter(uchar character) {
    // Reset char
    *s.cursor = 0x0;

    // Set char (text and bg color and character value)
    *s.cursor = (s.bgColor << 12) | (s.textColor << 8) | character;
    // Move the cursor
    s.cursor++;

    // Shift the screen
    // TODO : Check pointeur
    //ushort* val = (ushort *)FIRST_ADDR;
    //ushort* newVal = (ushort *)FIRST_ADDR;
    if (s.cursor > LAST_ADDR) {
        // Reset the cursor at the beginning of the line
        //s.cursor -= (SCREEN_WIDTH * 2);
        s.cursor -= SCREEN_WIDTH;
        //for (int i = 0; i < SCREEN_HEIGHT * (SCREEN_WIDTH - 1); i++, val++) {
        //    newVal = val + SCREEN_WIDTH;
        //    //*screen = (ushort *)screen + (ushort *)SCREEN_WIDTH;
        //    *val = *newVal;
        //}
        // Each line is replaced by the next one
        for (ushort* i = (ushort *)FIRST_ADDR; i < (ushort *)(LAST_ADDR - SCREEN_WIDTH); i++) {
            //newVal = i + SCREEN_WIDTH;
            *i = *(i + SCREEN_WIDTH);
            //*i = *newVal;
            //*i = *i + (ushort *)SCREEN_WIDTH; // KO
        }
        // Clear the last line
        for (ushort* i = (ushort *)LAST_ADDR; i >= (ushort *)(LAST_ADDR - SCREEN_WIDTH); i--) {
            //*i = 0x0;
            *i = (15 << 8) | 65;
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
void printf() {

}


////////////////////////////////////////////////////////////////////////////////////////
void setCursorPosition(uchar x, uchar y) {
    ushort pos = y * SCREEN_WIDTH + x;

    outb(0x3d4, 14);
    outw(0x3d5, (ushort)(pos >> 8));    // MSB of pos
    outb(0x3d4, 15);
    outw(0x3d5, (ushort)(pos & 255));   // LSB of pos

    s.cursor = (ushort *)FIRST_ADDR;    // Go to first address
    s.cursor += (ushort)pos;            // Add the pos
}


////////////////////////////////////////////////////////////////////////////////////////
void getCursorPosition(uchar* x, uchar* y) {
    int pos, msb, lsb;
    outb(0x3d4, 14);
    msb = (int)(inw(0x3d5)); // MSB of pos
    outb(0x3d4, 15);
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
// NOT USED
void lineToGrid(ushort pos, uchar* x, uchar* y) {
    // x is the division, y the modulo
    *x = (uchar)(((pos) - FIRST_ADDR) / SCREEN_WIDTH);
    *y = (uchar)(((pos) - FIRST_ADDR) % SCREEN_WIDTH);
}

