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
    //setCursorPosition(12, 20);
    //printCharacter('X');
    //printCharacter('Y');
    //setCursorPosition(1, 1);
    //printCharacter('a');
    //clearScreen();
    //setCursorPosition(0, 0);
    //printCharacter('A');
    //setCursorPosition(0, 5);
    //printCharacter('B');
    //printString("Hello");
    //setCursorPosition(5, 10);
    setTextColor(C_LIGHT_GREEN);
    setBackgroundColor(C_DARK_GRAY);
    //printCharacter('C');
    //setCursorPosition(77, 23);
    //printCharacter('E');
    //printString("Pikachu");

    //clearScreen();

    //for (int i = 0; i < SCREEN_HEIGHT; i++) {
    //    setCursorPosition(0, i);
    //    printCharacter(i + 48);
    //}

    //setCursorPosition(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    //printString("New Line");

    //setAllTextColor(C_BLACK);
    //setAllBackgroundColor(C_WHITE);
    //setTextColor(C_BLACK);
    //setBackgroundColor(C_WHITE);

    //int* x;
    //int* y;
    //getCursorPosition(x, y);
    //printf("Pos : (%d, %d)", *x, *y);

    //setTextColor(C_WHITE);
    //setBackgroundColor(C_BLACK);

    //clearScreen();

////////////////////////////////////////////////////////////////////////////////////////
    // Shift check
    // Print number on first column
    for (int i = 0; i < 70; i++) {
        setCursorPosition(0, i);
        printCharacter(i + 48);
    }

    // Writes some characters in order to shift the screen (with a delay)
    //for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i++) {
    //    printCharacter(i % 255);
    //    //sleep(15);
    //}
////////////////////////////////////////////////////////////////////////////////////////
    // Printf test
    //char *s = "printf function";
    //printf("Test : %s", s);

    //// char
    //char c1 = 'a';
    //char c2 = 'b';
    //printf("Test char : %c is followed by %c", c1, c2);

    //// integer
    //printf("Test integer : %d and %d (should be 4213 and 99)", 4213, 99);

    //// hex
    //printf("Test hex : %x and %x (should be 0xBABA and 0x42)", 0xBABA, 0x42);

////////////////////////////////////////////////////////////////////////////////////////
    // Cursor check (set / get)
    sleep(20);
    clearScreen();
    uchar x, y;
    x = 1;
    y = 1;
    printf("Set cursor position at (%d, %d).", x, y);
    setCursorPosition(x, y);
    getCursorPosition(&x, &y);
    //printf("Position after get function (%d, %d).", x, y);
    printf("(%d, %d)", x, y);
    setCursorPosition(0, 2);
    outb(0x23000, 'A');
    printf("%d", inb(0x23000));
////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////
void sleep(int c) {
    for (int i = 0; i < c * 1000; i++);
}
