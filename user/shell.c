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
#include "syscall.h"

void emptyBuffer(char* buffer, int size) {

    // Fill the buffer with zero
    for (int i = 0; i < size; i++) {
        buffer[i] = '\0';
    }
}

void split(char* buffer, char* args, int size) {

    // Parse the buffer
    int i = 0;
    while (buffer[i] != ' ') if (++i >= size) break;

    // Remove the spaces
    if (i < size) while (buffer[i] == ' ') buffer[i++] = '\0';

    // Place the args in the args buf
    for (int j = i; j < size; j++) {
        buffer[j] = '\0';
    }
}

void readBuffer(char* buffer, int size) {

    // Args buffer
    char args[size];
    emptyBuffer(args, size);

    // Split the command and its args
    split(buffer, args, size);

    // Launch the command with it's args
    // exec(buffer, args);
    syscall(SYSCALL_EXEC, (uint32_t)buffer, (uint32_t)args, (uint32_t)0, (uint32_t)0);
}

void main() {

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
        if (c == '\b')
            buffer[cursor--] = '\0';        // Remove the last character

        // ... as a return line
        else if (c == '\n') {

            // Read buffer and launch the command if it is found
            readBuffer(buffer, BUF_SIZE);

            // Empty the buffer and reset cursor
            emptyBuffer(buffer, BUF_SIZE);
            cursor = 0;
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
        }

        // Print the character
        //if (putc(c) < 0)
        //    printf("Error while printing character");
        putc(c);
    }
}

/*
 *
 * NE PAS IMPLEMENTER ls ICI !!!!!!
 *
 * Il doit etre implementer dans un fichier C
 * a part et le fichier binaire devra etre inclus dans notre PFS.
 *
 *
 * */
//void ls() {
//
//}
