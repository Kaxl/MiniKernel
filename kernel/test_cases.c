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

void runKernelTest() {

    initScreen();
    setCursorPosition(12, 20);
    printCharacter('X');
    printCharacter('Y');
    setCursorPosition(1, 1);
    printCharacter('a');
    clearScreen();
    setCursorPosition(0, 0);
    printCharacter('A');
    setCursorPosition(0, 5);
    printCharacter('B');
    printString("Hello");
    setCursorPosition(5, 10);
    setTextColor(C_LIGHT_GREEN);
    setBackgroundColor(C_DARK_GRAY);
    printCharacter('C');
    setCursorPosition(77, 23);
    printCharacter('E');
    printString("Pikachu");

    clearScreen();

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        setCursorPosition(0, i);
        printCharacter(i + 48);
    }

    setCursorPosition(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    printString("New Line");

    //setAllTextColor(C_BLACK);
    //setAllBackgroundColor(C_WHITE);

    //int* x;
    //int* y;
    //getCursorPosition(x, y);
    //printf("Pos : (%d, %d)", *x, *y);

    //setTextColor(C_WHITE);
    //setBackgroundColor(C_BLACK);

    clearScreen();

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        setCursorPosition(0, i);
        printCharacter(i + 48);
    }

    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i++) {
        printCharacter(i % 255);
        sleep(15);
    }

    printString("                              ");
    printString("BAAAAAAATMAAAAAN TADATADATADTADTADTADTADTADTA");
    printString("                              ");
    printString("Rudolf, tu vas te faire defoncer a CS ;)");
    printString("                                                            ");
    printString("BOOOOOOOOOM HEAAAAAADSHOOOOOOT !!!!!!!!!!!");
}
