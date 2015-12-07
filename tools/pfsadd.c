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

superblock_t getSuperBlock(char* img);

/**
 * @brief Add a file in the image
 *
 * @param img       image of destination (binary file)
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

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error while opening the file");
        return;
    }

    FILE* image = fopen(img, "r+b");
    if (image == NULL) {
        printf("Error while opening the file");
        return;
    }

    // Filename cannot be longer than 31 bytes
    if (strlen(filename) > 31) {
        printf("Error, the filename is too long");
    }

    // Set the pointer at the beginning of the file
    fseek(image, SEEK_SET, 0);
    // Load the superblock
    superblock_t* superblock = calloc(1, sizeof(superblock_t));
    fread(superblock, sizeof(superblock_t), 1, image);
    // Load the bitmap
    


    printf("Superblock\n");
    printf("signature : %s\n", superblock->signature);
    printf("nbSectorsB : %d\n", superblock->nbSectorsB);
    printf("bitmapSize : %d\n", superblock->bitmapSize);
    printf("nbFileEntries : %d\n", superblock->nbFileEntries);
    printf("fileEntrySize : %d\n", superblock->fileEntrySize);
    printf("nbDataBlocks : %d\n", superblock->nbDataBlocks);

    // Creation of file entry
    file_entry_t newFileEntry;
    strcpy(newFileEntry.filename, filename);
    //memcpy(newFileEntry.filename, filename, sizeof(filename));
    // Last character is 0 (end of string)
    newFileEntry.filename[31] = 0;

    // Calculate the size of a block
    int blockSize = superblock->nbSectorsB * SECTOR_SIZE;
    // Position to write the file entry
    // Look for the first free position after the bitmap
    int firstFileEntry = blockSize + superblock->bitmapSize * blockSize;
    printf("FirstEntry=%d\n", firstFileEntry);
    // Load the file entries
    file_entry_t* arrayFileEntries = calloc(superblock->fileEntrySize, superblock->nbFileEntries);
    fseek(image, firstFileEntry, SEEK_SET);
    fread(arrayFileEntries, sizeof(file_entry_t), superblock->nbFileEntries, image); 
    // Look for the first free position
    for (int i = 0; i < superblock->nbFileEntries; i++) {
        if (!arrayFileEntries[i].filename[0]) {
            // Add the file entry in the array
            arrayFileEntries[i] = newFileEntry;
            break;
        }
    }
    // Write the array of file entry in the image
    fseek(image, firstFileEntry, SEEK_SET);
    fwrite(arrayFileEntries, superblock->fileEntrySize, superblock->nbFileEntries, image);

    // Write the data
    // Run over the file from block size to block size
    // For each block, find the first free bitmap, set it has taken.
    // Then go to the corresponding block and fill it
    char* arrayData = calloc(sizeof(char), blockSize);
    while (fread(arrayData, sizeof(char), blockSize, image) > 0) {

    }


    // Close the files
    fclose(image);
    fclose(file);
}

void main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Error, not enough arguments\n");
        printf("pfsadd img file\n");
        printf("img : image representing the filesystem\n");
        printf("file : file to add into the filesystem\n");
        return;
    }

    pfsadd(argv[1], argv[2]);
}


