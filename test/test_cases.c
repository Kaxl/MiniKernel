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

    printf("TEST MODE\r\n");
    char filename[FILENAME_SIZE];
    file_iterator_t it = file_iterator();
    printf("Iterator\r\n");
    printf("sectorNumber=%d\r\n", it.sectorNumber);
    printf("posInSector=%d\r\n", it.posInSector);
    printf("lastSector=%d\r\n", it.lastSector);

    printf("Files in filesytem : \r\n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\r\n", filename);
    }

    printf("Check if exists : \r\n");
    printf("fileTest : %d\r\n", file_exists("fileTest"));
    printf("NoFile : %d\r\n", file_exists("NoFile"));

    char* fileSize = "fileTest";
    stat_t stat;
    file_stat(fileSize, &stat);
    printf("Size of %s : %d\r\n", fileSize, stat.size);

    char* fileRead = "lorem";
    file_stat(fileRead, &stat);
    //char buff[(stat.size % SECTOR_SIZE == 0) ? stat.size : (stat.size/SECTOR_SIZE + 1) * SECTOR_SIZE];
    char buff[1000000];

    file_read(fileRead, (void *)&buff);
    printf("buff : =====================\r\n%s\r\n================================\r\n", buff);

    char* fileToRemove = "lorem";
    printf("Removing %s\r\n", fileToRemove);
    file_remove(fileToRemove);
    printf("Check if %s exists\r\n", fileToRemove);
    printf("%s : %d\r\n", fileToRemove, file_exists(fileToRemove));
    printf("Files in filesytem : \r\n");
    it = file_iterator();
    while (file_next(filename, &it)) {
        printf("%s\r\n", filename);
    }
    printf("End of listing\n");

    file_stat(fileRead, &stat);
    //char buff2[(stat.size % SECTOR_SIZE == 0) ? stat.size : (stat.size/SECTOR_SIZE + 1) * SECTOR_SIZE];
    char buff2[10000];
    if (file_read(fileRead, (void *)&buff2) == 0)
        printf("Success\r\n");
    else
        printf("Failed\r\n");
    printf("buff : =====================\r\n%s\r\n================================\r\n", buff2);


    // Read a file

    // Stat of a file

    // Check if file exists

    // Remove a file

    // Check if file exists

    // Print all filename of file system with iterator

}
