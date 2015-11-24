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
#include "x86.h"
#include "pic.h"
#include "gdt.h"
#include "idt.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "screen.h"


void runKernel() {

    // Init of gdt
    gdt_init();

    // Init of screen
    initScreen();

    // Remap interruptions
    // Needs to be done before activate them
    pic_init();

    // Activation of interruption
    sti();

    // Init of idt
    idt_init();

    // Init of timer
    timer_init(DEFAULT_FREQ);

    // Init of keyboard with CH layout
    keyboard_init(LAYOUT_CH);

    // Messages of initialization
    printf("Starting GDT                                                           [  ");
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("Starting screen                                                        [  ");
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("Starting PIC                                                           [  ");
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("Enabling interruptions                                                 [  ");
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("Starting IDT                                                           [  ");
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("Starting timer at %d[Hz]                                              [  ", DEFAULT_FREQ);
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("Starting keyboard                                                      [  ");
    setTextColor(C_GREEN);
    printf("OK");
    setTextColor(C_WHITE);
    printf("  ]\r\n");

    printf("\r\nWelcome to Snapfish OS !\r\n");
    printf("> ");

    for (;;) {
        char c = (char)(getc());
        if ((int)(c) >= 0) {
            if (c == 'Q') {
                printf("\r\nShutdown of the system in 1 second.");
                sleep(1000);
                printf("\r\nNOW !");
                halt();
            }
            else {
                printf("%c", c);
            }
        }
    }
}
