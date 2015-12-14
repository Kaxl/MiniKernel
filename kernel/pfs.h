/*
 * =====================================================================================
 *
 *       Filename:  pfs.h
 *
 *    Description:  Functions to handle PFS
 *
 *        Version:  1.0
 *        Created:  12/09/2015 05:35:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (),
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */
#ifndef __PFS__H
#define __PFS__H

#include "../common/types.h"

#define SIGNATURE_SIZE  8
#define FILENAME_SIZE   32
#define SECTOR_SIZE     512         // Bytes
#define FILE_ENTRY_SIZE 256         // Bytes
#define INDEX_SIZE      ((FILE_ENTRY_SIZE - FILENAME_SIZE - 4) / 2)   // 4 for INT

/**
 * @brief Statistique structure
 */
typedef struct stat_t {
    uint32_t size;
} stat_t;

typedef struct file_iterator_t {
    uint32_t sectorNumber;      // Sector number (starting at 0)
    uint32_t posInSector;       // Position into the sector
    uint32_t lastSector;        // Last sector of the file entries table
} file_iterator_t;

/**
 * @brief Superblock structure
 */
typedef struct __attribute__((packed)) superblock_t {
    char signature[SIGNATURE_SIZE]; // Signature of the file system
    unsigned int nbSectorsB;        // Number of sectors by bloc
    unsigned int bitmapSize;        // Size of the bitmap in bloc
    unsigned int nbFileEntries;     // Number of file entries
    unsigned int fileEntrySize;     // Size of a file entry in byte
    unsigned int nbDataBlocks;      // Number of data blocs
} superblock_t;

int file_stat(char *filename, stat_t *stat);

int file_read(char *filename, void *buf);

int file_remove(char *filename);

int file_exists(char *filename);

/**
 * @brief Creation of the file iterator
 *
 * Set the position before the first file, 
 * this way, on the first call to file_next, we will search for
 * the next file entry and return it.
 * It allows us to have the iterator still pointing on the filename 
 * return by file_next after calling it, so the file_next function 
 * can be used in order functions.
 *
 * @return the file iterator just created
 */
file_iterator_t file_iterator();


/**
 * @brief Go to the next file and return the current one pointed by iterator
 *
 * Go set the iterator on the next file with the first byte not equal to 0
 * Copy memory at the current position of the iterator into the filename
 *
 * @param filename Filename return
 * @param it       Iterator
 *
 * @return 0 if there is no file left, else 1
 */
int file_next(char *filename, file_iterator_t *it);

int pfs_init();

#endif
