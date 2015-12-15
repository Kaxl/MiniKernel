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
    printf("LIST FILES\n");
    char filename[FILENAME_SIZE];
    file_iterator_t it = file_iterator();

    printf("Files in filesytem : \n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\n", filename);
    }

////////////////////////////////////////////////////////////////////////////////////////
    printf("REMOVE FILES\n");
    char* fileToRemove = "lorem";
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
    printf("READ FILES\n");
    char* fileToRead = "fileA";
    printf("Content of %s (Should be 'Rudy is the best')\n", fileToRead);
    char buffA[1024];
    file_read(fileToRead, (void *)&buffA);
    printf("%s\n", buffA);

////////////////////////////////////////////////////////////////////////////////////////
    printf("STAT FILES\n");


    //printf("Check if exists : \n");
    //printf("%s : %d\n", fileA, file_exists("fileA"));
    //printf("NoFile : %d\n", file_exists("NoFile"));

    //char* fileSize = "fileTest";
    //stat_t stat;
    //file_stat(fileSize, &stat);
    //printf("Size of %s : %d\n", fileSize, stat.size);

    //char* fileRead = "lorem";
    //file_stat(fileRead, &stat);
    ////char buff[(stat.size % SECTOR_SIZE == 0) ? stat.size : (stat.size/SECTOR_SIZE + 1) * SECTOR_SIZE];
    //char buff[1000000];

    //file_read(fileRead, (void *)&buff);
    //printf("buff : =====================\n%s\n================================\n", buff);


    //file_stat(fileRead, &stat);
    ////char buff2[(stat.size % SECTOR_SIZE == 0) ? stat.size : (stat.size/SECTOR_SIZE + 1) * SECTOR_SIZE];
    //char buff2[10000];
    //if (file_read(fileRead, (void *)&buff2) == 0)
    //    printf("Success\n");
    //else
    //    printf("Failed\n");
    //printf("buff : =====================\n%s\n================================\n", buff2);


    // Read a file

    // Stat of a file

    // Check if file exists

    // Remove a file

    // Check if file exists

    // Print all filename of file system with iterator

}
