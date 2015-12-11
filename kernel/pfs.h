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
    uint32_t position;  // Adresse du file entry courant (a l'initialisation, premier file entry
    uint32_
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

/**
 * @brief File entry structure
 */
typedef struct __attribute__((packed)) file_entry_t {
    char filename[FILENAME_SIZE];           // Name of the file
    unsigned int size;                      // Size of the file (4 bytes)
    unsigned short int index[INDEX_SIZE];   // Index of block (2 bytes)
} file_entry_t;

/**
 * @brief PFS Structure
 */
typedef struct __attribute__((packed)) pfs_t {
    superblock_t superblock;
    unsigned char* bitmap;
    file_entry_t* fileEntries;
    int firstFileEntry;
    int firstDataBlock;
    int blockSize;
} pfs_t;

int file_stat(char *filename, stat_t *stat);

int file_read(char *filename, void *buf);

int file_remove(char *filename);

int file_exists(char *filename);

file_iterator_t file_iterator();

int file_next(char *filename, file_iterator_t *it);




