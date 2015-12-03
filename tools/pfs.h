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

typedef struct superbloc_t {
    char signature[8];                // Signature of the file system
    unsigned int nb_sectors_b;          // Number of sectors by bloc
    unsigned int bitmap_size;           // Size of the bitmap in bloc
    unsigned int nb_file_entries;       // Number of file entries
    unsigned int file_entries_size;     // Size of a file entry in byte
    unsigned int nb_data_blocks;        // Number of data blocs
} superbloc_t;

typedef struct pfsconf_t {
    char* filename;
    int x;
    int y;
    int z;
} pfsconst_t;

#endif
