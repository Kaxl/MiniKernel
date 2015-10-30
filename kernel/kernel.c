/*
 * =====================================================================================
 *
 *       Filename:  kernel.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:22:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "kernel.h"
#include "../common/screen.h"

void kernel_main() {
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
    setTextColor(C_LIGHT_MAGENTA); // TODO : define pour les couleurs
    setBackgroundColor(C_YELLOW);
    printCharacter('C');
    setCursorPosition(77, 23);
    printCharacter('E');
    printString("Pikachu");

    //int* x;
    //int* y;
    //getCursorPosition(x, y);
    //printf("Pos : (%d, %d)", *x, *y);

    //for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i++) {
    //    printCharacter(i % 255);
    //    // TODO : faire fonction sleep pour ralentir l'affichage
    //}
}
