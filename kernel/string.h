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

