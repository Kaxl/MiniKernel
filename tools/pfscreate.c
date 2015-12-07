/*
 * =====================================================================================
 *
 *       Filename:  pfscreate.c
 *
 *    Description:  Create a PFS file empty
 *
 *        Version:  1.0
 *        Created:  12/03/2015 04:00:7 PM
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
#include "pfs.h"
#include "const.h"

/**
 * @brief
 *
 * @param data
 * @param size
 */
//void fill_zero(void* data, int size) {
//    // TODO: Not sector_size but bloc_size
//    for (int i = size; i < SECTOR_SIZE; i++) {
//        data[i] = '\0';
//    }
//}

// create an empty file with blocks of x size (must be a 512 multiple), with y file entries and with z data blocks available
/**
 * @brief
 *
 * @param filename
 * @param x
 * @param y
 * @param z
 */
void pfscreate(char* filename, int blockSize, int nbFileEntries, int dataBlocksAvailable) {
    // Verif if blockSize is a multiple of a sector size
    if ((blockSize % SECTOR_SIZE) != 0) {
        printf("\n[ERROR] Bloc size is not a multiple of sector size\n");
        return;
    }

    // Creation of the the superblock
    // Each data bloc is one bit
    superblock_t superblock = {
        .signature = SIGNATURE,
        .nbSectorsB = blockSize / SECTOR_SIZE,
        .bitmapSize = (dataBlocksAvailable % blockSize == 0) ? dataBlocksAvailable / blockSize : dataBlocksAvailable / blockSize + 1,
        .nbFileEntries = nbFileEntries,
        .fileEntrySize = FILE_ENTRY_SIZE,
        .nbDataBlocks = dataBlocksAvailable
    };
    int len = sizeof(struct superblock_t);
    unsigned char * raw = calloc(blockSize, sizeof(unsigned char));
    memcpy(raw, &superblock, len);

    // Create and fill the bitmap
    int bitmapSize = superblock.bitmapSize * blockSize;
    char* bitmap = calloc(bitmapSize, sizeof(char));

    // Initialize all of the file entries
    int fileEntriesSize = FILE_ENTRY_SIZE*(nbFileEntries + nbFileEntries % 2);
    char* fileEntries = calloc(fileEntriesSize, sizeof(char));

    // Initlalize all the data blocks
    int dataBlocksSize = dataBlocksAvailable * blockSize;
    char* dataBlocks = calloc(dataBlocksSize, sizeof(char));

    // Open of the file
    FILE* fp;
    fp = fopen(filename, "wb");

    // Write in the file all the blocs
    fwrite(raw, sizeof(unsigned char), blockSize, fp);
    fwrite(bitmap, sizeof(char), bitmapSize, fp);
    fwrite(fileEntries, sizeof(char), fileEntriesSize, fp);
    fwrite(dataBlocks, sizeof(char), dataBlocksSize, fp);
    
    // close the file
    fclose(fp);
    return;
}

void main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Error, not enough arguments\npfscreate FILENAME X Y Z\n");
        printf("filename : name of the PFS file\n");
        printf("x : size of one block (multiple of 512)\n");
        printf("y : number of file entries\n");
        printf("z : data blocks available \n" );
        return;
    }

    pfscreate(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
}

