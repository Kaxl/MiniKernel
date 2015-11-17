/*
 * =====================================================================================
 *
 *       Filename:  base.h
 *
 *    Description:  Basic functions to handle memory
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:15:40 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#ifndef _BASE_H_
#define _BASE_H_

#include "../common/types.h"

/**
 * @brief Fill memory with a constant byte
 *
 * The memset() function fills the first count bytes of the memory area
 * pointed to by dst with the constant byte value.
 *
 * @param dst   Memory area pointed to
 * @param value Constant byte
 * @param count Number of bytes
 *
 * @return
 */
extern void *memset(void *dst, int value, uint count);

/**
 * @brief Copy memory area
 *
 * The  memcpy() function copies count bytes from memory area src to memory area dst.
 * The memory areas must not overlap.
 *
 * @param dst   Destination
 * @param src   Source
 * @param count Number of bytes
 *
 * @return
 */
extern void *memcpy(void *dst, void *src, uint count);

/**
 * @brief Compares two strings
 *
 * The  strcmp() function compares the two strings s1 and s2.
 * It returns an integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2.
 *
 * @param p String one (s1)
 * @param q String two (s2)
 * @param n Number of bytes
 *
 * @return int (-1, 0, 1) following the size of the first string and the second one
 */
extern int strncmp(const char *p, const char *q, uint n);

#endif

