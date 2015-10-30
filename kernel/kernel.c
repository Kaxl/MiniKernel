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
#include "gdt.h"
#include "../common/screen.h"

void kernel_main() {
    // Init of gdt ???
    //gdt_init();

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

    clearScreen();

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        setCursorPosition(0, i);
        printCharacter(i + 48);
    }

    setCursorPosition(SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    //printCharacter('N');
    printString("New Line");

    //int* x;
    //int* y;
    //getCursorPosition(x, y);
    //printf("Pos : (%d, %d)", *x, *y);

    //for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH * 2; i++) {
    //    printCharacter(i % 255);
    //    sleep(100000);
    //    // TODO : faire fonction sleep pour ralentir l'affichage
    //}
}


void sleep(int c) {
    for (int i = 0; i < c * 1000; i++);
}
