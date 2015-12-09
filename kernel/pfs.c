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


////////////////////////////////////////////////////////////////////////////////////////
int file_stat(char *filename, stat_t *stat) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_read(char *filename, void *buf) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_remove(char *filename) {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_exists(char *filename) {
    for (int i = 0; i < pfs->superblock.nbFileEntries; i++) {
        if ((strcmp(pfs->fileEntries[i].filename, filename)) == 0) {
            return 1;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
file_iterator_t file_iterator() {

}

////////////////////////////////////////////////////////////////////////////////////////
int file_next(char *filename, file_iterator_t *it) {

}

