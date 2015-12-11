/*
 * =====================================================================================
 *
 *       Filename:  string.h
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

/**
 * @brief Compares two string
 *
 * @param str1  String 1
 * @param str2  String 2
 *
 * @return i    0 if string are equals
 *              < 0 if str1 < str2
 *              > 0 if str2 < str1
 */
extern int strcmp(char* str1, char* str2);

/**
 * @brief Convert an integer into a string
 *
 * @return
 **/
extern void itoa(int n, char* s);

/**
 * @brief Convert an integer into a string of hexa
 *
 * @return
 **/
extern void xtoa(int n, char* s);

