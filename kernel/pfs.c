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

static superblock_t superblock;

////////////////////////////////////////////////////////////////////////////////////////
int file_stat(char* filename, stat_t *stat) {
    // Check if file exists
    //if (file_exists(filename)) {
    //    // Find the file entry
    //    int fileEntry = getFileEntry(filename);
    //    // Calculate the size
    //    // Fill in the structure stat_t
    //}
    //else {
    //    return -1;
    //}
}

////////////////////////////////////////////////////////////////////////////////////////
int file_read(char* filename, void *buf) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_remove(char* filename) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_exists(char* filename) {
}

////////////////////////////////////////////////////////////////////////////////////////
file_iterator_t file_iterator() {
    file_iterator_t it;
    // Set the iterator at the first file entry
    int blockSize = SECTOR_SIZE * superblock.nbSectorsB;

    it.sectorNumber = blockSize * (superblock.bitmapSize + 1) / SECTOR_SIZE;
    it.posInSector = 0;
    it.lastSector = it.sectorNumber + (superblock.nbFileEntries * superblock.fileEntrySize / SECTOR_SIZE);
    return it;
}

////////////////////////////////////////////////////////////////////////////////////////
int file_next(char* filename, file_iterator_t *it) {
    // Look for the next file in the file entry
    char sector[SECTOR_SIZE];
    read_sector(it->sectorNumber, sector);

    // Copy the filename
    memcpy(filename, &sector[it->posInSector], FILENAME_SIZE);

    // Look for the next file
    do {
        it->posInSector += superblock.fileEntrySize;
        if (it->posInSector >= SECTOR_SIZE) {
            it->posInSector = 0;
            it->sectorNumber += 1;
            read_sector(it->sectorNumber, sector);
        }
    }
    while (!(sector[it->posInSector]) && it->sectorNumber <= it->lastSector);

    // Calculate return value
    if (filename)
        return 1;
    else
        return 0;
}

int pfs_init() {

    uchar data[512];
    // Load superblock
    read_sector(0, &data);
    memcpy(&superblock, &data, sizeof(superblock_t));

    printf("\r\nSuperblock\r\n");
    printf("Signature     : %s\r\n", superblock.signature);
    printf("NbSectorsB    : %d\r\n", superblock.nbSectorsB);
    printf("BitmapSize    :%d\r\n", superblock.bitmapSize);
    printf("NbFileEntries : %d\r\n", superblock.nbFileEntries);
    printf("FileEntrySize :%d\r\n", superblock.fileEntrySize);
    printf("NbDataBlocks  :%d\r\n", superblock.nbDataBlocks);
}
