#ifndef __PFS__H
#define __PFS__H

/*
 * =====================================================================================
 *
 *       Filename:  pfs.h
 *
 *    Description:  All the structures needed by PFS
 *                  __attribute__((packed)) is used to indicate to gcc not to
 *                  change size of structure field for optimizations
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

/**
 * @brief
 */
typedef struct __attribute__((packed)) superblock_t {
    char signature[8];              // Signature of the file system
    unsigned int nbSectorsB;        // Number of sectors by bloc
    unsigned int bitmapSize;        // Size of the bitmap in bloc
    unsigned int nbFileEntries;     // Number of file entries
    unsigned int fileEntrySize;     // Size of a file entry in byte
    unsigned int nbDataBlocks;      // Number of data blocs
} superblock_t;

/**
 * @brief
 */
typedef struct __attribute__((packed)) pfsconf_t {
    char* filename;
    int x;
    int y;
    int z;
} pfsconst_t;

/**
 * @brief File entry structure
 */
typedef struct __attribute__((packed)) file_entry_t {
    char filename[32];                  // Name of the file
    unsigned int size;                  // Size of the file (4 bytes)
    unsigned short int index[110];      // Index of block (2 bytes)
} file_entry_t;

typedef struct __attribute__((packed)) pfs_t {
    superblock_t superblock;
    unsigned char* bitmap;
    file_entry_t* fileEntries;
    int firstDataBlocks;
    int blockSize;
} pfs_t;

int loadPFS(pfs_t* pfs, char* img);

int unloadPFS(pfs_t* pfs);

#endif
