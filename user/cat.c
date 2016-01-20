/*
 * =====================================================================================
 *
 *       Filename:  cat.c
 *
 *    Description:  Implementation of cat command
 *                  Print content of a file
 *
 *        Version:  1.0
 *        Created:  01/20/2016 05:08:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (), Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "ulib.h"

void main(char* filename) {
    file_iterator_t it = get_file_iterator();
    char* f = NULL;

    printf("Reading : %s\n", filename);

    // Get the size of the file
    if (get_stat(filename, &stat) < 0) {
        printf("Error file : %s doesn't exist\n", filename);
        return;
    }

    // Create a buffer with the size of the file
    char buffer[stat.size];

    // Read de file
    if (read_file(filename, buffer) < 0) {
        printf("Error while reading : %s\n", filename);
        return;
    }

    printf("%s", buffer);
}


