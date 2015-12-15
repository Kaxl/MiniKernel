/*
 * =====================================================================================
 *
 *       Filename:  pfsdel.c
 *
 *    Description:  Remove a file from the image
 *
 *        Version:  1.0
 *        Created:  12/08/2015 06:53:30 PM
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

/**
 * @brief Delete un file in the image
 *
 * @param img       image
 * @param filename  filename to delete
 */
void pfsdel(char* img, char* filename) {

    // Declare the PFS structure in order to load it
    pfs_t* pfs = calloc(1, sizeof(pfs_t));

    // Load the PFS
    loadPFS(pfs, img);

    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Get the index of the file entry
    int index = getFileEntry(pfs, filename);

    for (int i = 0; i < INDEX_SIZE; i++) {
        // If index is 0, exit the loop
        if (!pfs->fileEntries[index].index[i]) {
            break;
        }
        // If the index is used
        else {
            // Set the bit in the bitmap to 0
            int indexFile = pfs->fileEntries[index].index[i];
            pfs->bitmap[indexFile / 8] &= ~(0x80 >> (indexFile % 8));
        }
    }

    // Remove first byte of file entry (in filename)
    pfs->fileEntries[index].filename[0] = '\0';

    // Write the array of file entry in the image
    fseek(image, pfs->firstFileEntry, SEEK_SET);
    fwrite(pfs->fileEntries, pfs->superblock.fileEntrySize, pfs->superblock.nbFileEntries, image);

    // Write the bitmap
    fseek(image, pfs->blockSize, SEEK_SET);
    fwrite(pfs->bitmap, sizeof(char), pfs->superblock.bitmapSize, image);

    // Close the image
    fclose(image);

    // Free the pfs structure
    unloadPFS(pfs);
}


void main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, not enough arguments\n");
        printf("pfsadd img file\n");
        printf("img : image representing the filesystem\n");
        printf("file : file to remove from the filesystem\n");
        return;
    }

    pfsdel(argv[1], argv[2]);
}


