/*
 * =====================================================================================
 *
 *       Filename:  pfslist.c
 *
 *    Description:  List the files present in the image
 *
 *        Version:  1.0
 *        Created:  12/03/2015 08:53:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pfs.h"
#include "const.h"

superblock_t getSuperBlock(char* img);

/**
 * @brief List the files present in the image
 *
 * @param img       image of destionation (binary file)
 */
void pfslist(char* img) {

    // Load the image
    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Set the pointer at the beginning of the file
    fseek(image, SEEK_SET, 0);
    
    // Get the superblock
    superblock_t* superblock = calloc(1, sizeof(superblock_t));
    fread(superblock, sizeof(superblock_t), 1, image);

    // Test printfs
    printf("Superblock\n");
    printf("signature : %s\n", superblock->signature);
    printf("nbSectorsB : %d\n", superblock->nbSectorsB);
    printf("bitmapSize : %d\n", superblock->bitmapSize);
    printf("nbFileEntries : %d\n", superblock->nbFileEntries);
    printf("fileEntrySize : %d\n", superblock->fileEntrySize);
    printf("nbDataBlocks : %d\n", superblock->nbDataBlocks);



    // Close the file
    fclose(image);
}

void main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error, not enough arguments\n");
        printf("pfslist img\n");
        printf("img : image representing the filesystem\n");
        return;
    }

    pfslist(argv[1]);
}


