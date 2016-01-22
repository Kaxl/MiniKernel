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

#ifndef __ULIB__H
#define __ULIB__H

#include "../common/types.h"
#include "../common/pfs.h"
#include "../common/string.h"

// Functions from string.h
extern int strcmp(const char* str1, const char* str2);
extern void itoa(int n, char* s);
extern void xtoa(int n, char* s);

// Exit function in asm
extern void exitpoint();

////////////////////////////////////////////////////////////////////////////////////////
// Files access
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Read the file and put it inside the buffer
 *
 * @param filename The file to read
 * @param buf The content of the file
 *
 * @return The return code
 */
extern int read_file(char *filename, uchar *buf);

/**
 * @brief Load the metadatas of a file and put them in stat
 *
 * @param filename The file to read
 * @param stat The metadata of the file
 *
 * @return The return code
 */
extern int get_stat(char *filename, stat_t *stat);

/**
 * @brief Remove a file from the FS
 *
 * @param filename The file to remove
 *
 * @return The return code
 */
extern int remove_file(char *filename);

/**
 * @brief Return the file iterator
 *
 * @return The file iterator
 */
extern file_iterator_t get_file_iterator();

/**
 * @brief Iterate to the next file get its name through filename
 *
 * @param filename Where the filename of the next file will be written
 * @param it Iterator that makes the iteration possible
 *
 * @return The return code
 */
extern int get_next_file(char *filename, file_iterator_t *it);

////////////////////////////////////////////////////////////////////////////////////////
// Processus
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Run a programm with its args
 *
 * @param filename
 * @param args
 *
 * @return
 */
extern int exec(char *filename, char* args);

/**
 * @brief Exit the programm
 */
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
/**
 * @brief Read the character that the user typed on keyboard
 *
 * @return Integer value of the character
 */
extern int getc();

/**
 * @brief Write a character to the screen
 *
 * @param c The character
 */
extern void putc(char c);

/**
 * @brief Write a string to the screen
 *
 * @param str The string
 */
extern void puts(char *str);

/**
 * @brief Write a string to the screen with format arguments
 *
 * @param fmt The whole string with the format of the different args
 * @param ... The args to replace with the format symbol inside the string
 */
extern void printf(char *fmt, ...);

////////////////////////////////////////////////////////////////////////////////////////
// Time functions
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief During a certain amount of time [ms], the kernel is sleeping
 *
 * @param ms The amount of time
 */
extern void sleep(uint ms);

/**
 * @brief Get the current ticks count of the system
 *
 * @return The ticks
 */
extern int get_ticks();

////////////////////////////////////////////////////////////////////////////////////////
// Cursor functions
////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Set the cursor at position (x,y) on the screen
 *
 * @param x The row on the screen
 * @param y The line on the screen
 *
 * @return The return code
 */
extern int setCursor(int x, int y);

#endif
