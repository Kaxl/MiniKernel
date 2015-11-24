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
#include "idt.h"
#include "screen.h"
#include "x86.h"
#include "pic.h"
#include "keyboard.h"
#include "timer.h"

void runKernel() {

    // Remap interruptions
    // Needs to be done before activate them
    pic_init();

#ifdef TEST
    gdt_init();
    runKernelTest();
#else
    // Init of gdt
    gdt_init();
    initScreen();

    // Activation of interruption
    sti();

    printf("Init of GDT - Done\r\n");
    printf("Init of screen - Done\r\n");
    // Init of idt
    idt_init();
    printf("Init of IDT - Done\r\n");

    // Init of timer
    timer_init(10000);
    printf("Init of Timer at 100[hz] - Done\r\n");

    printf("Welcome to Snapfish OS !\r\n");
    printf("You're awesome, what can I do for you on this beautiful day ?\r\n");

    for (;;) {
        char c = (char)(getc());
        if ((int)(c) >= 0) {
            if (c == 'Q') {
                printf("\r\nShutdown of the system in 1 second.");
                sleep(1000);
                printf("\r\nNOW !");
                halt();
            } else {
                printf("%c", c);
            }
        }
    }

#endif
}
