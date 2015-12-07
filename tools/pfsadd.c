/*
 * =====================================================================================
 *
 *       Filename:  pfsadd.c
 *
 *    Description:  Add a file into the filesystem
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

int allocBlock(unsigned char* bitmap, int size);

/**
 * @brief Add a file in the image
 *
 * Load the superblock, create the file entry at the right position, 
 * then write each block by finding a free emplacement in the 
 * bitmap and writing the data in the right block
 *
 * @param img       image of destination (binary file)
 * @param filename  file to write into the image
 */
void pfsadd(char* img, char* filename) {

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error while opening the file");
        return;
    }

    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Filename cannot be longer than 31 bytes
    if (strlen(filename) > 31) {
        printf("Error, the filename is too long");
    }

    // Set the pointer at the beginning of the file
    fseek(image, 0, SEEK_SET);

    // Load the superblock
    superblock_t* superblock = calloc(1, sizeof(superblock_t));
    fread(superblock, sizeof(superblock_t), 1, image);

    // Calculate the size of a block
    int blockSize = superblock->nbSectorsB * SECTOR_SIZE;

    // Load the bitmap
    unsigned char* bitmap = calloc(superblock->bitmapSize * blockSize / 8, sizeof(char));
    int bitmapSize = superblock->bitmapSize * blockSize / 8;
    fread(bitmap, sizeof(char), bitmapSize, image);
    // Set the first bitmap at 1, because we don't want to user it.
    bitmap[0] |= (0x1 << 7);
    
    // Creation of file entry
    file_entry_t newFileEntry;
    strcpy(newFileEntry.filename, filename);

    // Last character is 0 (end of string)
    newFileEntry.filename[31] = 0;

    // Position to write the file entry
    // Look for the first free position after the bitmap
    int firstFileEntry = blockSize + superblock->bitmapSize * blockSize;

    // Write the data
    // Run over the file from block size to block size
    // For each block, find the first free bitmap, set it has taken.
    // Then go to the corresponding block and fill it
    int firstDataBlock = firstFileEntry + superblock->nbFileEntries * superblock->fileEntrySize;
    char* arrayData = calloc(sizeof(char), blockSize);
    int index = 0;

    while (fread(arrayData, sizeof(char), blockSize, file) > 0) {
        // Get the first free block number
        int blockNumber = allocBlock(bitmap, bitmapSize);
        // Go in the right position in the file and write in it
        fseek(image, blockNumber * blockSize + firstDataBlock, SEEK_SET);
        fwrite(arrayData, blockSize, 1, image);
        // Write the block number into the index of the file entry
        newFileEntry.index[index] = blockNumber;
        index++;
    }

    // Load the file entries
    file_entry_t* arrayFileEntries = calloc(superblock->fileEntrySize, superblock->nbFileEntries);
    fseek(image, firstFileEntry, SEEK_SET);
    fread(arrayFileEntries, sizeof(file_entry_t), superblock->nbFileEntries, image); 

    // Look for the first free position
    for (int i = 0; i < superblock->nbFileEntries; i++) {
        if (!arrayFileEntries[i].filename[0]) {
            // Add the file entry in the array
            arrayFileEntries[i] = newFileEntry;
            break;
        }
    }

    // Write the array of file entry in the image
    fseek(image, firstFileEntry, SEEK_SET);
    fwrite(arrayFileEntries, superblock->fileEntrySize, superblock->nbFileEntries, image);

    // Write the bitmap
    fseek(image, blockSize, SEEK_SET);
    fwrite(bitmap, sizeof(char), bitmapSize, image);

    // Close the files
    fclose(image);
    fclose(file);
}

/**
 * @brief Allocate a block by setting it at 1 in the bitmap and return the block number
 *
 * Run over the bitmap to find the first free entry 
 * and return the corresponding block number
 *
 * The bitmap is an array of unsigned char, 
 * so we need to check each bit of the char separately
 *
 * @param bitmap    Bitmap of image
 * @param size      Size of bitmap (number of char)
 *
 * @return          The block number
 */
int allocBlock(unsigned char* bitmap, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            if (!(bitmap[i] & (0x8 >> j))) {
                bitmap[i] |= (0x8 >> j);
                return (i * 8 + (8 - j));
            }
        }
    }
}

void main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, not enough arguments\n");
        printf("pfsadd img file\n");
        printf("img : image representing the filesystem\n");
        printf("file : file to add into the filesystem\n");
        return;
    }

    pfsadd(argv[1], argv[2]);
}


