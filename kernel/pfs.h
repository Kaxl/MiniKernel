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

#include "../common/types.h"

/**
 * @brief Statistique structure
 */
typedef struct stat_t {
    uint32_t size;
} stat_t;

typedef struct iterator_t {
    uint32_t sectorNumber;
    uint32_t posInSector;
    uint32_t lastSector;
} iterator_t;

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
 * Set the position on the first file 
 *
 * @return the file iterator just created
 */
file_iterator_t file_iterator();

int file_next(char *filename, file_iterator_t *it);




