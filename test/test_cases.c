/*
 * =====================================================================================
 *
 *       Filename:  test_cases.c
 *
 *    Description:  Test case for kernel
 *
 *        Version:  1.0
 *        Created:  10/27/2015 04:36:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy (), axel.fahy@etu.hesge.ch
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "test_cases.h"
#include "../common/pfs.h"
#include "../kernel/screen.h"
#include "../kernel/timer.h"

////////////////////////////////////////////////////////////////////////////////////////
void runKernelTest() {

////////////////////////////////////////////////////////////////////////////////////////
    printf("\nLIST FILES\n");
    char filename[FILENAME_SIZE];
    file_iterator_t it = file_iterator();

    printf("Files in filesytem : \n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\n", filename);
    }

////////////////////////////////////////////////////////////////////////////////////////
    printf("\nREMOVE FILES\n");
    char* fileToRemove = "fileB";
    printf("Check if %s exists\n", fileToRemove);
    printf("%s : %d\n", fileToRemove, file_exists(fileToRemove));
    printf("Removing %s\n", fileToRemove);
    file_remove(fileToRemove);
    printf("Check if %s exists\n", fileToRemove);
    printf("%s : %d\n", fileToRemove, file_exists(fileToRemove));
    printf("Files in filesytem : \n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\n", filename);
    }

////////////////////////////////////////////////////////////////////////////////////////
    printf("\nREAD FILES\n");
    char* fileToRead = "fileA";
    printf("Content of %s (Should be 'Rudy is the best')\n", fileToRead);
    char buffA[1024];
    file_read(fileToRead, (void *)&buffA);
    printf("%s\n", buffA);

////////////////////////////////////////////////////////////////////////////////////////
    printf("STAT FILES\n");
    char* fileToStat = "fileA";
    stat_t stat;
    file_stat(fileToStat, &stat);
    printf("Size of %s is %d bytes (Should be 17 bytes)\n", fileToStat, stat.size);

}
