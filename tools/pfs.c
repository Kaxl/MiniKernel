/*
 * =====================================================================================
 *
 *       Filename:  pfs.c
 *
 *    Description:  Functions that are used by all PFS command are centralize here
 *
 *        Version:  1.0
 *        Created:  12/08/2015 09:53:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rudolf Hohn (), rudolf.hohn@etu.hesge.ch
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "pfs.h"

int loadSuperblock(superblock_t* superblock, char* img) {
    // Load the image
    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return -1;
    }

    // Set the pointer at the beginning of the file
    fseek(image, 0, SEEK_SET);
    
    // Get the superblock
    superblock = calloc(1, sizeof(superblock_t));
    fread(superblock, sizeof(superblock_t), 1, image);
}
