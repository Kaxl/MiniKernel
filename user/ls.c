/*
 * =====================================================================================
 *
 *       Filename:  ls.c
 *
 *    Description:  Implementation of ls command
 *                  List of files in the filesystem
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

void main() {
    file_iterator_t it = get_file_iterator();
    char* filename = NULL;
    int i = 0;

    while (get_next_file(filename, &it)) {
        printf("%d -> %s\n", i, filename);
        i++;
    }
}


