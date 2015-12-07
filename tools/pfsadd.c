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

    FILE* file = fopen(filename, "r+b");

    if (file == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Filename cannot be longer than 31 bytes
    if (strlen(filename) > 31) {
        printf("Error, the filename is too long");
    }

    // Creation of file entry
    file_entry_t fileEntry = NULL;
    file_entry.filename = filename;
    file_entry.filename[31] = 0;

    // Position to write the file entry
    // Look for the first free position after the bitmap
    int posFileEntry =

    // TODO : Fonction pour avoir le superblock.
    // Recuperer le nombre de secteurs par block pour connaitre la taille du superblock
    // et pouvoir le charger, bitmap size, ...

    // Write the data
    // Run over the file from block size to block size
    // For each block, find the first free bitmap, set it has taken.
    // Then go to the corresponding block and fill it


    // Close the file
    fclose(file);
}

void main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, not enough arguments\n");
        printf("pfsadd img file\n");
        printf("img : image representing the filesystem\n");
        printf("file : file to add into the filesystem\n");
    }

    pfsadd(argv[1], atoi(argv[2]));
}




