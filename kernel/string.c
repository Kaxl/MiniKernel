/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  Functions to handle strings, conversions, ...
 *
 *        Version:  1.0
 *        Created:  11/03/2015 04:06:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "string.h"

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

