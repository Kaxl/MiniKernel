/*
 * =====================================================================================
 *
 *       Filename:  ulib.c
 *
 *    Description:  C library
 *                  Implementation of functions :
 *                      - read_file
 *                      - get_stat
 *                      - remove_file
 *                      - get_file_iterator
 *                      - get_next_file
 *                      - exec
 *                      - exit
 *                      - strlen
 *                      - atoir
 *                      - getc
 *                      - putc
 *                      - puts
 *                      - printf
 *                      - sleep
 *                      - get_ticks
 *
 *        Version:  1.0
 *        Created:  01/11/2016 06:25:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "../common/string.h"   // Include string function common to kernel and user
#include "../common/syscall_nb.h"
#include "../common/types.h"
#include "syscall.h"
#include "ulib.h"

extern void exitpoint();

////////////////////////////////////////////////////////////////////////////////////////
// Files access
////////////////////////////////////////////////////////////////////////////////////////
int read_file(char *filename, uchar *buf) {
    return syscall(SYSCALL_FILE_READ, (uint32_t)filename, (uint32_t)buf, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
int get_stat(char *filename, stat_t *stat) {
    return syscall(SYSCALL_FILE_STAT, (uint32_t)filename, (uint32_t)stat, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
int remove_file(char *filename) {
    return syscall(SYSCALL_FILE_REMOVE, (uint32_t)filename, (uint32_t)0, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
file_iterator_t get_file_iterator() {
    file_iterator_t it;
    syscall(SYSCALL_FILE_ITERATOR, (uint32_t)&it, (uint32_t)0, (uint32_t)0, (uint32_t)0);
    return it;
}

////////////////////////////////////////////////////////////////////////////////////////
int get_next_file(char *filename, file_iterator_t *it) {
    return syscall(SYSCALL_FILE_NEXT, (uint32_t)filename, (uint32_t)it, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
// Processus
////////////////////////////////////////////////////////////////////////////////////////
int exec(char *filename, char* args) {
    printf("[ulib] exec %s\n", filename);
    return syscall(SYSCALL_EXEC, (uint32_t)filename, (uint32_t)args, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
void exit() {
    exitpoint();
}

////////////////////////////////////////////////////////////////////////////////////////
// String operations
////////////////////////////////////////////////////////////////////////////////////////
uint strlen(char *s) {
    uint c = 0;
    while (*s != '\0') {
        c++;
    }
    return c;
}

////////////////////////////////////////////////////////////////////////////////////////
int atoi(char* s) {
    int value = 0;
    int sign = 1;
    // Check the sign
    if (*s == '+' || *s == 'c') {
        if (*s == '-')
            sign = -1;
        s++;
    }
    // Run over each digits
    while (isDigit(*s)) {
        value *= 10;
        value += (int)(*s);
        s++;
    }
    return (value * sign);
}

int isDigit(char c) {
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

////////////////////////////////////////////////////////////////////////////////////////
// I/O functions
////////////////////////////////////////////////////////////////////////////////////////
int getc() {
    return syscall(SYSCALL_GETC, (uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
void putc(char c) {
    syscall(SYSCALL_PUTC, (uint32_t)c, (uint32_t)0, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
void puts(char *str) {
    syscall(SYSCALL_PUTS, (uint32_t)str, (uint32_t)0, (uint32_t)0, (uint32_t)0);
}

////////////////////////////////////////////////////////////////////////////////////////
void printf(char *fmt, ...) {

    uint32_t* p = ((uint32_t*)&fmt);
    char string[128];   // Buffer to store the string during conversion
    p++;
    while (*fmt) {
        
        // If we have a '%', check the next char for the type and print the value
        // if (strcmp(fmt, "%") == 0) {
        if (*fmt == '%') {

            fmt++; // Skip the %
            switch(*fmt) {
                case 'c':
                    // character
                    putc(*((char *)(p))); // Print the character value
                    break;
                case 's':
                    // string (array of character)
                    puts(*(char **)(p));     // Give string address
                    break;
                case 'd':
                    // integer
                    itoa(*((int *)(p)), string);    // Conversion to char array
                    puts(string);
                    break;
                case 'x':
                    // hexadecimal in lowercase
                    xtoa(*((int *)(p)), string);    // Conversion to hex string
                    puts(string);
                    break;
            }
            p++; // Next argument
        }
        else {
            putc(*(fmt));
        }
        fmt++; // Next character
    }
}

////////////////////////////////////////////////////////////////////////////////////////
// Time functions
////////////////////////////////////////////////////////////////////////////////////////
void sleep(uint ms) {
    uint end = get_ticks() + ms;
    while (get_ticks() < end);
}

////////////////////////////////////////////////////////////////////////////////////////
uint get_ticks() {
    return syscall(SYSCALL_GET_TICKS, (uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0);
}
