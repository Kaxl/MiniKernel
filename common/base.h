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
void *memset(void *dst, int value, uint count);

/**
 * @brief Copy memory area
 *
 * @param dst
 * @param src
 * @param count
 *
 * @return
 */
void *memcpy(void *dst, void *src, uint count);

/**
 * @brief
 *
 * @param p
 * @param q
 * @param n
 *
 * @return
 */
int strncmp(const char *p, const char *q, uint n);
