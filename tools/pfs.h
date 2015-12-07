#ifndef __PFS__H
#define __PFS__H

/*
 * =====================================================================================
 *
 *       Filename:  pfs.h
 *
 *    Description:  All the structures needed by PFS
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
typedef struct superblock_t {
    char signature[8];                  // Signature of the file system
    unsigned int nbSectorsB;          // Number of sectors by bloc
    unsigned int bitmapSize;           // Size of the bitmap in bloc
    unsigned int nbFileEntries;       // Number of file entries
    unsigned int fileEntriesSize;     // Size of a file entry in byte
    unsigned int nbDataBlocks;        // Number of data blocs
} superblock_t;


/**
 * @brief
 */
typedef struct pfsconf_t {
    char* filename;
    int x;
    int y;
    int z;
} pfsconst_t;


/**
 * @brief File entry structure
 */
typedef struct fileentry_t {
    char filename[32];                  // Name of the file
    unsigned int size;                  // Sie of the file (4 bytes)
    unsigned short int index[110];      // Index of block (2 bytes)
} fileentry_t;

#endif
