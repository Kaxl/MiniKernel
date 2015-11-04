/*
 * =====================================================================================
 *
 *       Filename:  test_cases.c
 *
 *    Description:  Test case for kernel
 *
 *        Version:  1.0
 *        Created:  10/27/2015 04:36:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (), axel.fahy@etu.hesge.ch
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "test_cases.h"
#include "../common/screen.h"

////////////////////////////////////////////////////////////////////////////////////////
void runKernelTest() {

    initScreen();

////////////////////////////////////////////////////////////////////////////////////////
    // Color check
    setCursorPosition(0, 0);
    printString("Test for color in...");
    setTextColor(C_RED);
    setBackgroundColor(C_BLACK);
    printf("3...");
    sleep(10000);
    setTextColor(C_BLUE);
    setBackgroundColor(C_WHITE);
    printf("2...");
    sleep(10000);
    setTextColor(C_DARK_GRAY);
    setBackgroundColor(C_YELLOW);
    printf("1...");
    sleep(20000);
    setAllTextColor(C_LIGHT_GREEN);
    setAllBackgroundColor(C_DARK_GRAY);
    printf("GO !");
    sleep(10000);
    for (int i = 0; i < 16; i++) {
        setAllTextColor(i);
        setAllBackgroundColor((i+1)%16);
        sleep(5000);
    }
////////////////////////////////////////////////////////////////////////////////////////
    // Scroll check
    sleep(20000);
    clearScreen();
    setCursorPosition(0, 0);
    printf("Scrolling check");
    sleep(20000);

    // Print number on first column
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        // Print in line
        setCursorPosition(0, i);
        printCharacter(i + 48);
        // Print in diagonale
        for (int j = i + 10; j < SCREEN_WIDTH; j+=10) {
            setCursorPosition(j, i);
            printCharacter(i + 48);
        }
    }
    sleep(10000);

    // Writes some characters in order to shift the screen (with a delay)
    int i = 0;  // Var for loop
    int j = 33; // Value in ascii table
    while (i < SCREEN_WIDTH * SCREEN_HEIGHT * 2) {
        printCharacter(j);
        sleep(15);
        i++;
        // Reset j to have only visible character
        if (j > 122)
            j = 33;
        else
            j++;
    }
////////////////////////////////////////////////////////////////////////////////////////
    // Printf test
    sleep(20000);
    clearScreen();
    setCursorPosition(0, 0);
    printf("Printf check\r\n");
    sleep(20000);
    char *s = "printf function";
    printf("Test : %s\r\n", s);
    sleep(10000);

    // char
    char c1 = 'a';
    char c2 = 'b';
    printf("Test char : %c is followed by %c\n", c1, c2);
    sleep(10000);

    // integer
    printf("Test integer : %d and %d (should be 4213 and 99)\r\n", 4213, 99);
    sleep(10000);

    // hex
    printf("Test hex : %x and %x (should be 0xBABA and 0x42)\r\n", 0xBABA, 0x42);
    sleep(20000);

////////////////////////////////////////////////////////////////////////////////////////
    // Cursor check (set / get)
    sleep(20000);
    clearScreen();
    setCursorPosition(0, 0);
    printf("Cursor check\r\n");
    uchar x, y;
    x = 20;
    y = 20;
    printf("Set cursor position at (%d, %d).", x, y);
    setCursorPosition(x, y);
    getCursorPosition(&x, &y);
    //printf("Position after get function (%d, %d).", x & (0x00FF), y & (0x00FF));
    printf("Position after get function (%d, %d).", x, y);
////////////////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////////////
void sleep(int c) {
    for (int i = 0; i < c * 1000; i++);
}
