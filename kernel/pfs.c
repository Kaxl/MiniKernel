/*
 * =====================================================================================
 *
 *       Filename:  pfs.c
 *
 *    Description:  Implementation of function to handle PFS
 *
 *        Version:  1.0
 *        Created:  12/09/2015 05:34:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (), Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "../common/types.h"
#include "base.h"
#include "pfs.h"
#include "ide.h"
#include "base.h"
#include "screen.h"
#include "string.h"

static superblock_t superblock;

/**
 * @brief Move the iterator on the next file
 *
 * @param it Iterator to move
 */
static void findNextIterator(file_iterator_t *it);

////////////////////////////////////////////////////////////////////////////////////////
int file_stat(char* filename, stat_t *stat) {
    file_iterator_t it = file_iterator();
    char sector[SECTOR_SIZE];
    char file[FILENAME_SIZE];

    int size = 0;

    // Find the file
    while (file_next(file, &it)) {
        if (strcmp(file, filename) == 0) {
            read_sector(it.sectorNumber, sector);
            // Get the size
            memcpy(size, &sector[it.posInSector + FILENAME_SIZE], 4);
            return size;
        }
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////
int file_read(char* filename, void *buf) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_remove(char* filename) {
    file_iterator_t it = file_iterator();
    char sector[SECTOR_SIZE];
    char bitmap[SECTOR_SIZE];
    char file[FILENAME_SIZE];

    // Find the file
    while (file_next(file, &it)) {
        if (strcmp(file, filename) == 0) {
            read_sector(it.sectorNumber, sector);
            // Set the first byte of filename at 0
            sector[it.posInSector] = 0;
            write_sector(it.sectorNumber, sector);
            // Look for each bitmap
            // First index is at byte 36 (4 is the size of field 'File size')
            int index = it.posInSector + FILENAME_SIZE + 4;
            while (index < superblock.fileEntrySize) {
                int indexBitmap;
                memcpy(filename, &sector[index], 2);
                if (indexBitmap != 0) {
                    // Get the right sector
                    indexBitmap /= 8;   // Divison by 8 because each entry of the bitmap is a byte
                    read_sector((indexBitmap / 8) / SECTOR_SIZE, bitmap);
                    // Get the position in the sector
                    char byteIndex = bitmap[(indexBitmap / 8) % SECTOR_SIZE];

                }
                else {
                    break;
                }
                index += 2; // Each index is on 2 bytes
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
int file_exists(char* filename) {
    file_iterator_t it = file_iterator();

    char file[FILENAME_SIZE];

    while (file_next(file, &it)) {
        if (strcmp(file, filename) == 0)
            return 1;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
file_iterator_t file_iterator() {
    file_iterator_t it;
    // Set the iterator at the first file entry
    int blockSize = SECTOR_SIZE * superblock.nbSectorsB;

    it.sectorNumber = blockSize * (superblock.bitmapSize + 1) / SECTOR_SIZE;
    it.posInSector = SECTOR_SIZE - superblock.fileEntrySize;
    it.lastSector = it.sectorNumber + (superblock.nbFileEntries * superblock.fileEntrySize / SECTOR_SIZE);
    // Init a previous block so when whe call file_next, we have the first file
    it.sectorNumber--;
    return it;
}

////////////////////////////////////////////////////////////////////////////////////////
int file_next(char* filename, file_iterator_t *it) {
    char sector[SECTOR_SIZE];
    // Look for the next file
    findNextIterator(it);

    // Look for the next file in the file entry
    read_sector(it->sectorNumber, sector);

    // Copy the filename
    memcpy(filename, &sector[it->posInSector], FILENAME_SIZE);

    // If there is no filename (first byte), return 0
    if (!filename[0]) {
        return 0;
    }

    return 1;
}

static void findNextIterator(file_iterator_t *it) {
    // Look for the next file in the file entry
    char sector[SECTOR_SIZE];
    char filename[FILENAME_SIZE];
    read_sector(it->sectorNumber, sector);

    // Look for the next file
    do {
        it->posInSector += superblock.fileEntrySize;
        if (it->posInSector >= SECTOR_SIZE) {
            it->posInSector = 0;
            it->sectorNumber++;
            read_sector(it->sectorNumber, sector);
        }
        // Copy the filename
        memcpy(filename, &sector[it->posInSector], FILENAME_SIZE);
    }
    while (!(filename[0]) && it->sectorNumber <= it->lastSector);
}

int pfs_init() {

    uchar data[SECTOR_SIZE];
    // Load superblock
    read_sector(0, &data);
    memcpy(&superblock, &data, sizeof(superblock_t));

    printf("\r\nSuperblock\r\n");
    printf("Signature     : %s\r\n", superblock.signature);
    printf("NbSectorsB    : %d\r\n", superblock.nbSectorsB);
    printf("BitmapSize    : %d\r\n", superblock.bitmapSize);
    printf("NbFileEntries : %d\r\n", superblock.nbFileEntries);
    printf("FileEntrySize : %d\r\n", superblock.fileEntrySize);
    printf("NbDataBlocks  : %d\r\n", superblock.nbDataBlocks);
}
