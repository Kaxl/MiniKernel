/*
 * =====================================================================================
 *
 *       Filename:  pfsadd.c
 *
 *    Description:  Add a file into the filesystem
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

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pfs.h"
#include "const.h"

/**
 * @brief Add a file in the image
 *
 * @param img       image of destionation (binary file)
 * @param filename  file to write into the image
 */
void pfsadd(char* img, char* filename) {

    // 1. Aller apres les bitmaps
    //
    //      prendre le 1er emplacement libre pour le fileentry, verifier si on a pas attend le nombre maximul de fileentry
    //
    //
    // 2. Data
    //      Parcourir le fichier de taille bloc en taille bloc
    //      Pour chaque bloc :
    //          trouver le 1er bitmap libre
    //          indiquer le 1er bitmap dans le fileentry
    //          mettre data dans le bloc

    FILE* f = fopen(filename, "r+b");

    if (f == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Creation of file entry

    // Write the file entry
    // Look for the first free position after the bitmap

    // Write the data
    // Run over the file from block size to block size
    // For each block, find the first free bitmap, set it has taken.
    // Then go to the corresponding block and fill it

    // Open of the file
    FILE* fp;
    fp = fopen(filename, "wb");



    // Close the file
    fclose(f);

    return;
}

void main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, not enough arguments\npfscreate FILENAME X Y Z\n");
        printf("img : image representing the filesystem\n");
        printf("file : file to add into the filesystem\n");
    }

    pfsadd(argv[1], atoi(argv[2]));
}




