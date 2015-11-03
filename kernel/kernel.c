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
#include "../test/test_cases.h"
#include "gdt.h"
#include "../common/screen.h"

void runKernel() {

#ifdef TEST
    gdt_init();
    runKernelTest();
#else
    // Init of gdt ???
    gdt_init();

    initScreen();
    printString("Welcome to Snapfish OS !");
    setCursorPosition(0, 1);
    printString("You're awesome, what can I do for you on this beautiful day ?");
#endif

}

