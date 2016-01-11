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

#include "syscall_nb.h"

extern int syscall(uint32_t nb, uint32_t arg1, uint32_t arg2, uint32_t arg3, utint32_t arg4);

////////////////////////////////////////////////////////////////////////////////////////
// Files access
////////////////////////////////////////////////////////////////////////////////////////
int read_file(char *filename, uchar *buf) {
    return syscall(SYSCALL_FILE_READ, filename, buf);
}

////////////////////////////////////////////////////////////////////////////////////////
int get_stat(char *filename, stat_t *stat) {
    return syscall(SYSCALL_FILE_STAT, filename, stat);
}

////////////////////////////////////////////////////////////////////////////////////////
int remove_file(char *filename) {
    return syscall(SYSCALL_FILE_REMOVE, filename);
}

////////////////////////////////////////////////////////////////////////////////////////
file_iterator_t get_file_iterator() {
    file_iterator_t it;
    return syscall(SYSCALL_FILE_ITERATOR, &it);
}

////////////////////////////////////////////////////////////////////////////////////////
int get_next_file(char *filename, file_iterator_t *it) {
    return syscall(SYSCALL_FILE_NEXT, filename, it);
}

////////////////////////////////////////////////////////////////////////////////////////
// Processus
////////////////////////////////////////////////////////////////////////////////////////
int exec(char *filename) {
    int ret = syscall(SYSCALL_EXEC, filename);
    if (ret < 0)
        printf("Error while executing : %s", filename);
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////
void exit() {
    // TODO
}

////////////////////////////////////////////////////////////////////////////////////////
// String operations
////////////////////////////////////////////////////////////////////////////////////////
uint strlen(char *s) {
    uint c = 0;
    while (*s != '\0') {
        c++
    }
    return c;
}

////////////////////////////////////////////////////////////////////////////////////////
int atoi(char *s) {
    int value = 0;
    int signe = 1;
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
int strcmp(char* str1, char* str2) {
    int i = 0;
    while (str1[i] == str2[i] && str1[i] != '\0')
        i++;

    if (str1[i] == str2[i])
        return 0;
    else if (str2[i] > str1[i])
        return 1;
    else if (str1[i] < str2[i])
        return -1;
    else
        return -1;
}

////////////////////////////////////////////////////////////////////////////////////////
void itoa(int n, char* s) {
    char* p = s;
    char const *digit = "0123456789";

    // Number is negative so we have to print a '-' before
    if (n < 0) {
        *(p++) = '-';
        n *= -1;
    }

    // If n = 0
    if (n == 0)
        p++;

    // Save the size of the array
    int tmp_n = n;
    while (tmp_n) {
        tmp_n = tmp_n / 10;
        p++;
    }

    // Adding the last character
    *p = '\0';

    // Write the integer from the back
    tmp_n = n;
    while (tmp_n) {
        *(--p) = digit[tmp_n%10];
        tmp_n = tmp_n / 10;
    }

    // If n = 0
    if (n == 0)
        *(--p) = digit[0];
}

////////////////////////////////////////////////////////////////////////////////////////
void xtoa(int n, char* s) {
    char* p = s;
    char const *hexa = "0123456789ABCDEF";

    // Number is negative so we have to print a '-' before
    if (n < 0) {
        *(p++) = '-';
        n *= -1;
    }

    // As n is a hex number, we have to print '0x' before
    *(p++) = '0';
    *(p++) = 'x';

    // Save the size of the array
    int tmp_n = n;
    while (tmp_n) {
        tmp_n = tmp_n / 16;
        p++;
    }

    // Adding the last character
    *p = '\0';

    // Write the hex from the back
    tmp_n = n;
    while (tmp_n) {
        *(--p) = hexa[tmp_n%16];
        tmp_n = tmp_n / 16;
    }
}


////////////////////////////////////////////////////////////////////////////////////////
// I/O functions
////////////////////////////////////////////////////////////////////////////////////////
int getc() {
    return syscall(SYSCALL_GETC);
}

////////////////////////////////////////////////////////////////////////////////////////
void putc(char c) {
    syscall(SYSCALL_PUTC, c);
}

////////////////////////////////////////////////////////////////////////////////////////
void puts(char *str) {
    syscall(SYSCALL_PUTS, str);
}

////////////////////////////////////////////////////////////////////////////////////////
void printf(char *fmt, ...) {

    uint32_t* p = ((uint32_t*)&fmt);
    char string[128];   // Buffer to store the string during conversion
    p++;
    while (*fmt) {
        // If we have a '%', check the next char for the type and print the value
        if (strncmp(s, "%", 1) == 0) {
            fmt++; // Skip the %
            switch(*fmt) {
                case 'c':
                    // character
                    syscall_putc(*((char *)(p))); // Print the character value
                    break;
                case 's':
                    // string (array of character)
                    syscall_putc(*(char **)(p));     // Give string address
                    break;
                case 'd':
                    // integer
                    itoa(*((int *)(p)), string);    // Conversion to char array
                    syscall_putc(string);
                    break;
                case 'x':
                    // hexadecimal in lowercase
                    xtoa(*((int *)(p)), string);    // Conversion to hex string
                    syscall_putc(string);
                    break;
            }
            p++; // Next argument
        }
        else {
            syscall_putc(*(fmt));
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
    return syscall(SYSCALL_GET_TICKS);
}

