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
 *         Author:  Rudolf Hohn, Axel Fahy
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "pfs.h"

//========================================================
// Local functions to load all PFS data
int loadSuperblock(superblock_t* superblock, FILE* image);

int loadBitmap(unsigned char** bitmap, FILE* image, superblock_t* superblock, int blockSize);

int loadFileEntries(file_entry_t** fileEntries, FILE* image, superblock_t* superblock, int blockSize);

int unloadSuperblock(superblock_t* superblock);

int unloadBitmap(unsigned char** bitmap);

int unloadFileEntries(file_entry_t** fileEntries);
//========================================================


int loadSuperblock(superblock_t* superblock, FILE* image) {

    // Get the superblock
    if (fread(superblock, sizeof(superblock_t), 1, image) < 0) {
        printf("Error while reading file\n");
        return -1;
    }

    return 0;
}

int loadBitmap(unsigned char** bitmap, FILE* image, superblock_t* superblock, int blockSize) {

    // Position the cursor at the beginning of the bitmap
    fseek(image, blockSize, SEEK_SET);

    // Get the bitmap
    int bitmapSize = superblock->bitmapSize * blockSize / 8;
    *bitmap = calloc(bitmapSize, sizeof(char));
    fread(*bitmap, sizeof(char), bitmapSize, image);
}

int loadFileEntries(file_entry_t** fileEntries, FILE* image, superblock_t* superblock, int blockSize) {

    // Position the cursor at the beginning of the file entries
    fseek(image, blockSize + superblock->bitmapSize * blockSize, SEEK_SET);

    // Get the file entries
    *fileEntries = calloc(superblock->fileEntrySize, superblock->nbFileEntries);
    fread(*fileEntries, sizeof(file_entry_t), superblock->nbFileEntries, image);
}

int loadPFS(pfs_t* pfs, char* img) {

    // Load the image
    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return -1;
    }

    // Set the pointer at the beginning of the file
    fseek(image, 0, SEEK_SET);

    // Get the superblock
    loadSuperblock(&pfs->superblock, image);

    // Calculate the size of a block
    pfs->blockSize = pfs->superblock.nbSectorsB * SECTOR_SIZE;

    // Calculate the first file entry
    pfs->firstFileEntry = pfs->blockSize + pfs->superblock.bitmapSize * pfs->blockSize;

    // Calculate the first data block
    int actualSizeFE = pfs->superblock.nbFileEntries * FILE_ENTRY_SIZE;
    pfs->firstDataBlock = pfs->firstFileEntry + FILE_ENTRY_SIZE * (pfs->superblock.nbFileEntries + (pfs->blockSize - actualSizeFE) / FILE_ENTRY_SIZE);

    // Load the bitmap
    loadBitmap(&pfs->bitmap, image, &pfs->superblock, pfs->blockSize);

    // Load the file entries
    loadFileEntries(&pfs->fileEntries, image, &pfs->superblock, pfs->blockSize);
}

int unloadSuperblock(superblock_t* superblock) {

    // Free the superblock structure
    free(superblock);

    return 0;
}

int unloadBitmap(unsigned char** bitmap) {

    // Free the bitmap
    free(*bitmap);

    return 0;
}

int unloadFileEntries(file_entry_t** fileEntries) {

    // Free the file entries
    free(*fileEntries);

    return 0;
}

int unloadPFS(pfs_t* pfs) {

    // Unload all the memory allocated for the structure
    //unloadSuperblock(&pfs->superblock);
    //unloadFileEntries(&pfs->fileEntries);
    //unloadBitmap(&pfs->bitmap);

    // Free the structure
    free(pfs);

    return 0;
}
