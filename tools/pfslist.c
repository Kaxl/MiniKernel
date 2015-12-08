/*
 * =====================================================================================
 *
 *       Filename:  pfslist.c
 *
 *    Description:  List the files present in the image
 *
 *        Version:  1.0
 *        Created:  12/03/2015 08:53:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pfs.h"
#include "const.h"

/**
 * @brief List the files present in the image
 *
 * @param img       image of destionation (binary file)
 */
void pfslist(char* img) {

    // Declare the PFS structure in order to load it
    pfs_t* pfs = calloc(1, sizeof(pfs_t));

    // Load the PFS
    loadPFS(pfs, img);

    // Look for files in file entry
    for (int i = 0; i < pfs->superblock.nbFileEntries; i++) {

        // Stop the reading if no more file entries with data
        if (!pfs->fileEntries[i].filename[0]) {
            break;
        }

        // Print the filename
        printf("%s\n", pfs->fileEntries[i].filename);
    }

    // Free the pfs structure
    unloadPFS(pfs);
}

void main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error, not enough arguments\n");
        printf("pfslist img\n");
        printf("img : image representing the filesystem\n");
        return;
    }

    pfslist(argv[1]);
}


