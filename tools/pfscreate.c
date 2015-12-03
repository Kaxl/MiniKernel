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

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pfs.h"
#include "const.h"

void fill_zero(void* data, int size) {
    // TODO: Not sector_size but bloc_size
    for (int i = size; i < SECTOR_SIZE; i++) {
        data[i] = '\0';
    }
}

// create an empty file with blocks of x size (must be a 512 multiple), with y file entries and with z data blocks available 
void pfscreate(char* filename, int x, int y, int z) {
    // Verif if x is a multiple of a sector size
    if ((x % SECTOR_SIZE) != 0) {
        printf("\n[ERROR] Bloc size is not a multiple of sector size\n");
        return;
    }

    // Creation of the the superbloc
    // Each data bloc is one bit
    superbloc_t superbloc = {
        .signature = SIGNATURE,
        .nb_sectors_b = x / SECTOR_SIZE,
        .bitmap_size = z / 8,
        .nb_file_entries = y,
        .file_entries_size = FILE_ENTRY_SIZE,
        .nb_data_blocks = z
    };

    // Create and fill the bitmap
    char bitmap_size[superbloc.bitmap_size + (superbloc.bitmap_size % z)];
    
    // Initialize all of the file entries
    

    // Initlalize all the data blocks


    // Open of the file
    FILE* fp;
    fp = fopen(filename, "wb");
    
    // Write in the file all the blocs


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
    }

    pfscreate(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
}

