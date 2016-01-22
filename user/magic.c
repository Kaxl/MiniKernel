/*
 * =====================================================================================
 *
 *       Filename:  magic.c
 *
 *    Description:  Magic program
 *
 *        Version:  1.0
 *        Created:  01/21/2016 09:53:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (),
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "ulib.h"

static void printFile(char* filename) {
    stat_t stat;
    if (get_stat(filename, &stat) < 0)
        printf("Error while getting size of %s\n", filename);

    uchar b[stat.size];

    if (read_file(filename, b) < 0)
        printf("Error while reading %s\n", filename);

    printf("%s\n", b);
    sleep(2000);
}

// Lets play the magic ...
void main() {
    printFile("a.txt");
    printFile("b.txt");
    printFile("c.txt");
}
