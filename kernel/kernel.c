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
#include "pfs.h"

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

    pfs_init();

    char filename[FILENAME_SIZE];
    file_iterator_t it = file_iterator();
    printf("Iterator\r\n");
    printf("sectorNumber=%d\r\n", it.sectorNumber);
    printf("posInSector=%d\r\n", it.posInSector);
    printf("lastSector=%d\r\n", it.lastSector);

    printf("Files in filesytem : \r\n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\r\n", filename);
    }

    printf("Check if exists : \r\n");
    printf("fileTest : %d\r\n", file_exists("fileTest"));
    printf("NoFile : %d\r\n", file_exists("NoFile"));

    char* fileSize = "fileTest";
    stat_t stat;
    file_stat(fileSize, &stat);
    printf("Size of %s : %d\r\n", fileSize, stat.size);

    char* fileRead = "fileTest";
    file_stat(fileRead, &stat);
    //char buff[stat.size];
    char buff[SECTOR_SIZE*2];
    printf("[fileRead] size of fileTest : %d\r\n", stat.size);
    file_read(fileRead, (void *)&buff);

    printf("buff : =============\r\n%s\r\n", buff);

    char* fileToRemove = "lorem";
    printf("Removing %s\r\n", fileToRemove);
    file_remove(fileToRemove);
    printf("Check if %s exists\r\n", fileToRemove);
    printf("%s : %d\r\n", fileToRemove, file_exists(fileToRemove));
    printf("Files in filesytem : \r\n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\r\n", filename);
    }

    // Init PFS
    //if (pfs_init() < 0) {
    //    printf("Problem during init of PFS\r\n");
    //    halt();
    //}


    // Read a file

    // Stat of a file

    // Check if file exists

    // Remove a file

    // Check if file exists

    // Print all filename of file system with iterator




    //for (;;) {
    //    char c = (char)(getc());
    //    if ((int)(c) >= 0) {
    //        if (c == 'Q') {
    //            printf("\r\nShutdown of the system in 1 second.");
    //            sleep(1000);
    //            printf("\r\nNOW !");
    //            halt();
    //        }
    //        else {
    //            printf("%c", c);
    //        }
    //    }
    //}
}
