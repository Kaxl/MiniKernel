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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pfs.h"

//========================================================
// Local functions to load all PFS data
int loadSuperblock(superblock_t* superblock, FILE* image);

int loadBitmap(unsigned char* bitmap, FILE* image);

int loadFileEntries(file_entry_t* fileEntries, FILE* image);

int unloadSuperblock(superblock_t* superblock);

int unloadBitmap(unsigned char* bitmap);

int unloadFileEntries(file_entry_t* fileEntries);
//========================================================


//int openFile(FILE* image, char* img) {
//    
//    // Load the image
//    image = fopen(img, "r+b");
//    if (image == NULL) {
//        printf("Error while opening the file\n");
//        return -1;
//    }
//
//    // Set the pointer at the beginning of the file
//    fseek(image, 0, SEEK_SET);
//}

int loadSuperblock(superblock_t* superblock, FILE* image) {
    
    // Load the image
    //FILE* image;
    //if (openFile(image, img) < 0)
    //    return -1;
    
    // Get the superblock
    superblock = calloc(1, sizeof(superblock_t));
    if (fread(superblock, sizeof(superblock_t), 1, image) < 0) {
        printf("Error while reading file\n");
        return -1;
    }

    // Close the file
    //fclose(image);
}

int loadBitmap(unsigned char* bitmap, FILE* image, superblock_t* superblock) {

}

int loadFileEntries(file_entry_t* fileEntries, FILE* image, superblock_t* superblock) {
    
    // Load the file entries
    fileEntries = calloc(superblock->fileEntrySize, superblock->nbFileEntries);
    fseek(image, blockSize + superblock->bitmapSize * blockSize, SEEK_SET);
    fread(arrayFileEntries, sizeof(file_entry_t), superblock->nbFileEntries, image); 
}

int loadPFS(pfs_t* pfs, char* img) {

    // Load the image
    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Set the pointer at the beginning of the file
    fseek(image, 0, SEEK_SET);
    
    // Get the superblock
    loadSuperblock(pfs->superblock);
    //superblock_t* superblock = calloc(1, sizeof(superblock_t));
    //fread(superblock, sizeof(superblock_t), 1, image);

    // Calculate the size of a block
    pfs->blockSize = superblock->nbSectorsB * SECTOR_SIZE;
    
    // Load the file entries
    loadFileEntries(pfs->fileEntries, image, pfs->superblock);
    //file_entry_t* arrayFileEntries = calloc(superblock->fileEntrySize, superblock->nbFileEntries);
    //fseek(image, blockSize + superblock->bitmapSize * blockSize, SEEK_SET);
    //fread(arrayFileEntries, sizeof(file_entry_t), superblock->nbFileEntries, image); 
}

int unloadSuperblock(superblock_t* superblock) {
    
    // Free the superblock structure
    free(superblock);
    return 0;
}

int unloadBitmap(unsigned char* bitmap) {

}

int unloadFileEntries(file_entry_t* fileEntries) {

}

int unloadPFS(pfs_t* pfs) {
    free(pfs);
}
