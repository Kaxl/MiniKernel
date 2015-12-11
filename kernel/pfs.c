/*
 * =====================================================================================
 *
 *       Filename:  pfs.c
 *
 *    Description:  Implementation of function to handle PFS
 *
 *        Version:  1.0
 *        Created:  12/09/2015 05:34:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (), Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "../common/types.h"
#include "pfs.h"
#include "ide.h"
#include "base.h"
#include "screen.h"

static superblock_t superblock;

////////////////////////////////////////////////////////////////////////////////////////
int file_stat(char *filename, stat_t *stat) {
    // Check if file exists
    // Find the file entry
    // Calculate the size
    // Fill in the structure stat_t

}

////////////////////////////////////////////////////////////////////////////////////////
int file_read(char *filename, void *buf) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_remove(char *filename) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_exists(char *filename) {
    // Load pfs structure

    //for (int i = 0; i < pfs->superblock.nbFileEntries; i++) {
    //    if ((strcmp(pfs->fileEntries[i].filename, filename)) == 0) {
    //        return 1;
    //    }
    //}
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
file_iterator_t file_iterator() {
    // Charge le tableau de files entries
    // Mets la position a la premier fileentry non vide
}

////////////////////////////////////////////////////////////////////////////////////////
int file_next(char *filename, file_iterator_t *it) {
    // Chercher le prochain fichier par rapport a la position courante de l'iterateur
    // copy le nom du fichier dans filename.
    // Si on arrive a la fin du tableau de file entries, arrete
}

int pfs_init() {

    uchar data[512];
    // Load superblock
    read_sector(0, &data);
    memcpy(&superblock, &data, sizeof(superblock_t));

    printf("\r\nSuperblock\r\n");
    printf("%s\r\n", superblock.signature);
    printf("%d\r\n", superblock.nbSectorsB);
    printf("%d\r\n", superblock.bitmapSize);
    printf("%d\r\n", superblock.nbFileEntries);
    printf("%d\r\n", superblock.fileEntrySize);
    printf("%d\r\n", superblock.nbDataBlocks);
}
