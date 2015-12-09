/*
 * =====================================================================================
 *
 *       Filename:  pfs.h
 *
 *    Description:  Functions to handle PFS
 *
 *        Version:  1.0
 *        Created:  12/09/2015 05:35:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (),
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

/**
 * @brief Statistique structure
 */
typedef struct {
    uint32_t size;
} stat_t;


int file_stat(char *filename, stat_t *stat);

int file_read(char *filename, void *buf);

int file_remove(char *filename);

int file_exists(char *filename);

file_iterator_t file_iterator();

int file_next(char *filename, file_iterator_t *it);




