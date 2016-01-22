/*
 * =====================================================================================
 *
 *       Filename:  shell.c
 *
 *    Description:  Where the kernel is hidden.
 *
 *        Version:  1.0
 *        Created:  01/11/2016 07:47:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rudolf Hohn, Axel Fahy
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "shell.h"
#include "../common/syscall_nb.h"
#include "ulib.h"
#include "../common/string.h"
#include "syscall.h"

////////////////////////////////////////////////////////////////////////////////////////
static void printShell() {

    // Init the buffer
    stat_t stat;
    get_stat(SHELL_SCREEN, &stat);
    uchar buffer[stat.size];

    // Load the shell image
    if (read_file(SHELL_SCREEN, buffer) < 0) {
        printf("Error while loading shell image.\n");
        return;
    }

    // Print the shell image
    printf("%s\n",buffer);
}

////////////////////////////////////////////////////////////////////////////////////////
static void emptyBuffer(char* buffer, int size) {

    // Fill the buffer with zero
    for (int i = 0; i < size; i++) {
        buffer[i] = '\0';
    }
}

////////////////////////////////////////////////////////////////////////////////////////
static void split(char* buffer, char* args, int size) {

    // Parse the buffer
    int i = 0;
    while (buffer[i] != ' ') if (++i >= size) break;

    // Remove the spaces
    if (i < size) while (buffer[i] == ' ') buffer[i++] = '\0';

    // Place the args in the args buf
    for (int j = i; j < size; j++) {
        args[j-i] = buffer[j];
        buffer[j] = '\0';
    }
}

////////////////////////////////////////////////////////////////////////////////////////
static void readBuffer(char* buffer, int size) {

    // Args buffer
    char args[size];
    emptyBuffer(args, size);

    // Split the command and its args
    split(buffer, args, size);

    if (strcmp(buffer, "help") == 0) {
        help();
    }
    else if (strcmp(buffer, "ls") == 0) {
        ls();
    }
    else if (strcmp(buffer, "cat") == 0) {
        cat(args);
    }
    else if (strcmp(buffer, "rm") == 0) {
        rm(args);
    }
    else if (strcmp(buffer, "ticks") == 0) {
        ticks();
    }
    else if (strcmp(buffer, "sleep") == 0) {
        sleep((uint)(atoi(args)));
    }
    else if (strcmp(buffer, "exit") == 0) {
        exit();
    }
    else if (strcmp(buffer, "run") == 0) {
        run(args);
    } else {
        printf("\nCommand not found : %s\n", buffer);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void main() {
    printShell();
    printf(" > ");

    // Init the buffer of CLI and empty it
    char buffer[BUF_SIZE];
    emptyBuffer(buffer, BUF_SIZE);
    int cursor = 0;

    // Init current character
    char c = '\0';

    // Infinite loop to manage the CLI
    for (;;) {
        // Get the current character
        if ((c = getc()) < 0)
            continue;

        // Manage the character locally
        // ... as a backspace
        if (c == '\b') {
            if (cursor > 0)
                buffer[cursor--] = '\0';        // Remove the last character
        }

        // ... as a return line
        else if (c == '\n') {
            // Read buffer and launch the command if it is found
            if (cursor > 0) {
                readBuffer(buffer, BUF_SIZE);

                // Empty the buffer and reset cursor
                emptyBuffer(buffer, BUF_SIZE);
                cursor = 0;
            }
            printf(" > ");
        }

        // ... as anything else
        else {

            // Buffer full
            if (cursor == BUF_SIZE) {
                printf("Buffer char is full, please press [ENTER].\n");
                continue;
            }

            // Insert the character in buffer
            buffer[cursor++] = c;
            // Print the character
            putc(c);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ls() {
    file_iterator_t it = get_file_iterator();
    char filename[100];

    while (get_next_file(filename, &it)) {
        printf("%s\n", filename);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void cat(char* filename) {
    stat_t stat;
    stat.size = 0;

    printf("Reading : %s\n", filename);

    // Get the size of the file
    if (get_stat(filename, &stat) < 0) {
        printf("Error file : %s doesn't exist\n", filename);
        return;
    }
    printf("Stat : %d\n", stat.size);
    if (stat.size < 0) {
        printf("Error with the size of the file\n");
        return;
    }

    // Create a buffer with the size of the file
    uchar buffer[stat.size];

    // Read de file
    if (read_file(filename, buffer) < 0) {
        printf("Error while reading : %s\n", filename);
        return;
    }

    printf("%s", buffer);
}

////////////////////////////////////////////////////////////////////////////////////////
void rm(char* filename) {
    if (remove_file(filename) < 0) {
        printf("Error while removing : %s\n", filename);
    }
}

void run(char* filename) {
    if (exec(filename, NULL) < 0) {
        printf("Error when executing : %s\n", filename);
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void ticks() {
    uint t = get_ticks();
    printf("Ticks : %d\n", t);
}

////////////////////////////////////////////////////////////////////////////////////////
void help() {
    // print the help for users
    printf("ls \t\t\t: List all file on the disk.\n");
    printf("cat FILE \t: Print the content of a file.\n");
    printf("rm FILE \t: Delete a file from the disk.\n");
    printf("run FILE \t: Run a program.\n");
    printf("ticks \t\t: Display the current ticks count.\n");
    printf("sleep N \t: Wait for N millisecond.\n");
    printf("help \t\t: Display this help.\n");
}
