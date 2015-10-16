/*
 * =====================================================================================
 *
 *       Filename:  base.c
 *
 *    Description:  Basic functions to handle memory
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:12:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */


////////////////////////////////////////////////////////////////////////////////////////
void *memset(void *dst, int value, uint count) {
    unsigned char* p=dst;
    while (count--)
        *p++ = (unsigned char) value;
    return dst;
}


////////////////////////////////////////////////////////////////////////////////////////
void *memcpy(void *dst, void *src, uint count) {
    char *dp = dst;
    const char *sp = src;
    while (n--)
        *dp++ = *sp++;
    return dst
}


////////////////////////////////////////////////////////////////////////////////////////
int strncmp(const char *p, const char *q, uint n) {
    while (n--)
        if (*p++ != *q++)
            return *(unsigned char*)(p - 1) - *(unsigned char*)(q - 1);
    return 0;
}

