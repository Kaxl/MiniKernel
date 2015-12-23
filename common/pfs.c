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

#include "types.h"
#include "../kernel/base.h"
#include "pfs.h"
#include "../kernel/ide.h"
#include "../kernel/base.h"
#include "../kernel/screen.h"
#include "string.h"

static superblock_t superblock;

/**
 * @brief Move the iterator on the next file
 *
 * @param it Iterator to move
 */
static void setIteratorOnNextFile(file_iterator_t *it);

////////////////////////////////////////////////////////////////////////////////////////
int file_stat(char* filename, stat_t *stat) {
    file_iterator_t it = file_iterator();
    char sector[SECTOR_SIZE];
    char file[FILENAME_SIZE];

    // Find the file
    while (file_next(file, &it)) {
        if (strcmp(file, filename) == 0) {
            read_sector(it.sectorNumber, sector);
            // Get the size
            stat->size = (uint32_t)sector[it.posInSector + FILENAME_SIZE];
            return 0;
        }
    }
    return -1;
}

////////////////////////////////////////////////////////////////////////////////////////
int file_read(char* filename, void *buf) {

    char* buff = (char *)buf;

    // Initiate the file iterator
    file_iterator_t it = file_iterator();

    // Current filename when iterating
    char file[FILENAME_SIZE];
    char fileEntry[SECTOR_SIZE];

    // Index used to navigate through the blocks on disk
    unsigned short int currentIndexBlock;

    // Semi-constant value used for multiple operations
    int blockSize = superblock.nbSectorsB * SECTOR_SIZE;

    // Iterate through the image while there are more files
    while (file_next(file, &it)) {

        // If this is the file we are looking for
        if (strcmp(file, filename) == 0) {
            // Read the sector where the file entry is
            read_sector(it.sectorNumber, fileEntry);

            // Index inside the file entry
            int index = 36; // 36 is for 32B for the filename and 4B for the size

            // The padding is done to skip the superblock, bitmap and file entries
            int paddingByte = (blockSize + superblock.bitmapSize * blockSize + superblock.nbFileEntries * superblock.fileEntrySize);
            int paddingBlock = paddingByte / blockSize;
            if (paddingByte % blockSize != 0)
                paddingBlock++;

            // Index of the block read inside the file entry
            currentIndexBlock = (ushort)fileEntry[index + it.posInSector];

            // While there are blocks to read
            while (currentIndexBlock != 0) {

                // For one block, maybe we have to read multiple sectors
                for (unsigned int i = 0; i < superblock.nbSectorsB; i++) {

                    // Read the sector and go the next one
                    read_sector((currentIndexBlock + paddingBlock) * superblock.nbSectorsB + i, buff);
                    buff += SECTOR_SIZE;
                }

                // Going at the next index
                index += sizeof(ushort);
                currentIndexBlock = (ushort)fileEntry[index + it.posInSector];
            }
            return 0;
        }
    }
    return -1;
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
            int indexFileEntry = it.posInSector + FILENAME_SIZE + 4;
            unsigned short int indexData = (unsigned short int)sector[indexFileEntry];
            //int indexData = sector[indexFileEntry];
            while (indexData != 0) {
                // Find the sector with the bitmap
                // We need to divise by 8 because each entry of the bitmap is a byte
                int sectorNumber = ((indexData / 8) / SECTOR_SIZE) + superblock.nbSectorsB;
                // Bitmap start at 0
                read_sector(sectorNumber, bitmap);
                bitmap[indexData / 8] &= ~(0x80 >> (indexData % 8));
                write_sector(sectorNumber, bitmap);
                // Go to the next index
                indexFileEntry += 2;
                indexData = (unsigned short int)sector[indexFileEntry]; // Each index is on 2 bytes
            }
            return 0;
        }
    }
    return -1;
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

    // +1 for the superblock
    it.sectorNumber = blockSize * (superblock.bitmapSize + 1) / SECTOR_SIZE;
    it.posInSector = SECTOR_SIZE - superblock.fileEntrySize;
    it.lastSector = it.sectorNumber + (superblock.nbFileEntries * superblock.fileEntrySize / SECTOR_SIZE) - 1;
    // Init a previous block so when we call file_next, we have the first file
    it.sectorNumber--;
    return it;
}

////////////////////////////////////////////////////////////////////////////////////////
int file_next(char* filename, file_iterator_t *it) {
    char sector[SECTOR_SIZE];
    // Look for the next file
    setIteratorOnNextFile(it);

    // Look for the next file in the file entry
    read_sector(it->sectorNumber, sector);

    // Copy the filename
    memcpy(filename, &sector[it->posInSector], FILENAME_SIZE);
    //printf("[file_next] : %s\n", filename);

    // If there is no filename (first byte), return 0
    if (!filename[0]) {
        return 0;
    }

    return 1;
}

static void setIteratorOnNextFile(file_iterator_t *it) {
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
    return 0;
}
