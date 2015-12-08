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
int getNumberFreeBlocksLeft(unsigned char* bitmap, int bitmapSize);
int filenameExist(pfs_t* pfs, const char* filename);
unsigned long getFileSize(const char* filename);

/**
 * @brief Add a file in the image
 *
 * Load the superblock, create the file entry at the right position,
 * then write each block by finding a free emplacement in the
 * bitmap and writing the data in the right block
 *
 * @param img       image of destination (binary file)
 * @param filename  file to write into the image
 *
 * @return          If result < 0, error
 */
int pfsadd(char* img, char* filename) {

    // PFS structure
    pfs_t pfs;

    // Load the PFS structure
    if ((loadPFS(&pfs, img)) < 0) {
        return -1;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error while opening the file");
        return -1;
    }

    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return -1;
    }

    // Filename cannot be longer than 31 bytes
    if (strlen(filename) > 31) {
        printf("Error, the filename is too long");
        return -1;
    }

    // Set the pointer at the beginning of the file
    fseek(image, 0, SEEK_SET);

    // Check for the space left on device
    int bitmapSize = pfs.superblock.bitmapSize * pfs.blockSize / 8;
    int nbFreeBlocks = getNumberFreeBlocksLeft(pfs.bitmap, bitmapSize);

    unsigned long fileSize = getFileSize(filename);
    if (nbFreeBlocks - (int)((fileSize / pfs.blockSize) + 1) < 0) {
        printf("Not enought space left on device\n");
        return -1;
    }

    // Check if filename already exists
    if (filenameExist(&pfs, filename)) {
        printf("Filename already exists\n");
        return -1;
    }

    // Creation of file entry
    file_entry_t newFileEntry;
    strcpy(newFileEntry.filename, filename);

    // Last character is 0 (end of string)
    newFileEntry.filename[31] = 0;

    // Look for the first free position after the bitmap
    int posNewFileEntry = -1;
    for (int i = 0; i < pfs.superblock.nbFileEntries; i++) {
        if (!pfs.fileEntries[i].filename[0]) {
            // Save the position of the file entry,
            // the file entry is add at the end
            posNewFileEntry = i;
            // Add the file entry in the array
            //pfs->fileEntries[i] = newFileEntry;
            break;
        }
    }
    // If the fileEntries array is full, exit
    if (posNewFileEntry == -1) {
        printf("File entries are full\n");
        return -1;
    }

    // Write the data
    // Run over the file from block size to block size
    // For each block, find the first free bitmap, set it has taken.
    // Then go to the corresponding block and fill it
    char* arrayData = calloc(sizeof(char), pfs.blockSize);
    int index = 0;

    int blockNumber;
    while (fread(arrayData, sizeof(char), pfs.blockSize, file) > 0) {

        // Get the first free block number
        blockNumber = allocBlock(pfs.bitmap, bitmapSize);
        if (blockNumber < 0) {
            printf("Error while writing the file\n");
            return -1;
        }

        // Go in the right position in the file and write in it
        fseek(image, blockNumber * pfs.blockSize + pfs.firstDataBlock, SEEK_SET);
        fwrite(arrayData, pfs.blockSize, 1, image);

        // Write the block number into the index of the file entry
        newFileEntry.index[index] = blockNumber;
        index++;
    }

    // Position to write the file entry
    int firstFileEntry = pfs.blockSize + pfs.superblock.bitmapSize * pfs.blockSize;
    pfs.fileEntries[posNewFileEntry] = newFileEntry;

    // Write the array of file entry in the image
    fseek(image, firstFileEntry, SEEK_SET);
    fwrite(pfs.fileEntries, pfs.superblock.fileEntrySize, pfs.superblock.nbFileEntries, image);

    // Write the bitmap
    fseek(image, pfs.blockSize, SEEK_SET);
    fwrite(pfs.bitmap, sizeof(char), pfs.superblock.bitmapSize, image);

    // Close the files
    fclose(image);
    fclose(file);

    // Free the memory
    unloadPFS(&pfs);
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
    // For the first char, we don't test the first bit, because we can't use it.
    for (int i = 0; i < size; i++) {
        // If all bits are taken
        if (bitmap[i] == 0xf) {
            continue;
        }
        for (int j = 6; j >= 0; j--) {
            if (!(bitmap[i] & (0x1 << j))) {
                bitmap[i] |= (0x1 << j);
                return (i * 0x8 + (0x8 - j));
            }
        }
    }
    // Start at the second char
    for (int i = 0; i < size; i++) {
        // If all bits are taken
        if (bitmap[i] == 0xf) {
            continue;
        }
        for (int j = 7; j >= 0; j--) {
            if (!(bitmap[i] & (0x1 << j))) {
                bitmap[i] |= (0x1 << j);
                return (i * 0x8 + (0x8 - j));
            }
        }
    }
    return -1;
}

/**
 * @brief Get the number of free blocks left on the device
 *
 * Run over the bitmap and increment a counter each time a bit is at 0.
 *
 * @param bitmap        Bitmap of the file
 * @param bitmapSize    Size of bitmap
 *
 * @return              The number of free blocks
 */
int getNumberFreeBlocksLeft(unsigned char* bitmap, int bitmapSize) {
    int cnt = 0;
    // For the first char, we don't test the first bit, because we can't use it.
    for (int i = 0; i < bitmapSize; i++) {
        for (int j = 6; j >= 0; j--) {
            if (!(bitmap[i] & (0x1 << j))) {
                cnt++;
            }
        }
    }
    // Start at the second char
    for (int i = 1; i < bitmapSize; i++) {
        // If all bits are taken
        if (bitmap[i] == 0xf) {
            continue;
        }
        for (int j = 7; j >= 0; j--) {
            if (!(bitmap[i] & (0x1 << j))) {
                cnt++;
            }
        }
    }
    return cnt;
}

/**
 * @brief Check if a filename already exists on the image
 *
 * @param pfs       Filesystem loaded
 * @param filename  Filename
 *
 * @return          0 if doesn't exist, else 1
 */
int filenameExist(pfs_t* pfs, const char* filename) {
    for (int i = 0; i < pfs->superblock.nbFileEntries; i++) {
        if ((strcmp(pfs->fileEntries[i].filename, filename)) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Get the size of a file
 *
 * @param filename File to get the size from
 *
 * @return The size of the file
 */
unsigned long getFileSize(const char* filename) {
  unsigned long size;
  FILE* f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  size  = ftell(f);
  fclose(f);
  return size;
}


void main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, not enough arguments\n");
        printf("pfsadd img file\n");
        printf("img : image representing the filesystem\n");
        printf("file : file to add into the filesystem\n");
        return;
    }

    if ((pfsadd(argv[1], argv[2]) < 0))
        printf("Error when adding the file\n");
}

