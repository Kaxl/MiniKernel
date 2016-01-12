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
extern int read_file(char *filename, uchar *buf);

extern int get_stat(char *filename, stat_t *stat);

extern int remove_file(char *filename);

extern file_iterator_t get_file_iterator();

extern int get_next_file(char *filename, file_iterator_t *it);

////////////////////////////////////////////////////////////////////////////////////////
// Processus
////////////////////////////////////////////////////////////////////////////////////////
extern int exec(char *filename);

extern void exit();

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
extern uint strlen(char *s);

/**
 * @brief Conversion of a string to an integer
 *
 * @param s String to convert
 *
 * @return The integer value of the strint
 */
extern int atoi(char *s);

/**
 * @brief Check if character is a digit
 *
 * @param c Character to test
 *
 * @return Value different from 0 if a digit, else 0
 */
extern int isDigit(char c);

////////////////////////////////////////////////////////////////////////////////////////
// I/O functions
////////////////////////////////////////////////////////////////////////////////////////
extern int getc();

extern void putc(char c);

extern void puts(char *str);

extern void printf(char *fmt, ...);

////////////////////////////////////////////////////////////////////////////////////////
// Time functions
////////////////////////////////////////////////////////////////////////////////////////
extern void sleep(uint ms);

extern uint get_ticks();



