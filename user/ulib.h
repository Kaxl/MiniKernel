/*
 * =====================================================================================
 *
 *       Filename:  ulib.h
 *
 *    Description:  Header of ulib.c
 *
 *        Version:  1.0
 *        Created:  01/11/2016 06:27:38 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn 
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */


////////////////////////////////////////////////////////////////////////////////////////
// Files access
////////////////////////////////////////////////////////////////////////////////////////
int read_file(char *filename, uchar *buf);

int get_stat(char *filename, stat_t *stat);

int remove_file(char *filename);

file_iterator_t get_file_iterator();

int get_next_file(char *filename, file_iterator_t *it);

////////////////////////////////////////////////////////////////////////////////////////
// Processus 
////////////////////////////////////////////////////////////////////////////////////////
int exec(char *filename);

void exit();

////////////////////////////////////////////////////////////////////////////////////////
// String operations
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Return the number of character in a string
 *
 * @param s String to count
 *
 * @return The length of the string
 */
uint strlen(char *s);

/**
 * @brief Conversion of a string to an integer
 *
 * @param s String to convert
 *
 * @return The integer value of the strint
 */
int atoi(char *s);

/**
 * @brief Check if character is a digit
 *
 * @param c Character to test
 *
 * @return Value different from 0 if a digit, else 0
 */
int isDigit(char c);

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


////////////////////////////////////////////////////////////////////////////////////////
// I/O functions
////////////////////////////////////////////////////////////////////////////////////////
int getc();

void putc(char c);

void puts(char *str);

void printf(char *fmt, ...);

////////////////////////////////////////////////////////////////////////////////////////
// Time functions
////////////////////////////////////////////////////////////////////////////////////////
void sleep(uint ms);

uint get_ticks();



