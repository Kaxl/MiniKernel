/*
 * =====================================================================================
 *
 *       Filename:  screen.h
 *
 *    Description:  Function for the screen management.
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:21:47 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "../common/types.h"
#include "colors.h"
#include "controller.h"

#define SCREEN_WIDTH    80
#define SCREEN_HEIGHT   25
#define FIRST_ADDR_HEX  0xB8000
#define FIRST_ADDR      753664
#define LAST_ADDR       FIRST_ADDR + SCREEN_WIDTH * SCREEN_HEIGHT * 2 - 2
#define CHAR_COUNT      SCREEN_WIDTH * SCREEN_HEIGHT

/**
 * Screen structure to store the cursor position
 * and the colors (text and background)
 */
typedef struct screen {
    ushort* cursor;     // Cursor position absolute pointer on display memory
    uchar textColor;    // Text color
    uchar bgColor;      // Background color
} screen;

/**
 * @brief Initialization of the screen
 *
 * Clear the screen, set the cursor's position at top left
 * and set the default color for the text and background.
 *
 * @return
 */
extern void initScreen();

/**
 * @brief Clear the screen
 *
 * Clear the screen but keep the properties.
 *
 * @return
 */
extern void clearScreen();

/**
 * @brief Set the text color of all the screen
 * and change the current text color.
 *
 * @paramn color
 * @return
 */
extern void setAllTextColor(uchar color);

/**
 * @brief Set the text color
 *
 * All characters written after this call will be with
 * this new color.
 *
 * @param color Color to set
 * @return
 */
extern void setTextColor(uchar color);

/**
 * @brief Get the text color
 *
 * @return The current color
 */
extern uchar getTextColor();

/**
 * @brief Set the background color of all the screen
 * and changes the current background color.
 *
 * @param color Color to set
 * @return
 */
extern void setAllBackgroundColor(uchar color);

/**
 * @brief Set the background color
 *
 * All background of characters written after this call will be with
 * this new color.
 *
 * @param color
 * @return
 */
extern void setBackgroundColor(uchar color);

/**
 * @brief Get the background color
 *
 * @return The current background color
 */
extern uchar getBackgroundColor();

/**
 * @brief Print a character
 *
 * The character is print at the current cursor's position.
 * Then, the cursor is moved forward.
 * The color (text and background) of the character is the last one set.
 *
 * @param character Character to print
 * @return
 */
extern void printCharacter(char character);


/**
 * @brief Print a string
 *
 * @return
 */
extern void printString(char* string);

/**
 * @brief Printf function
 *
 * Each time we found a '%', we check the type and get the next argument.
 *
 * Implementations of %c, %s, %d, %x
 *
 * %c : character
 *
 * %s : string
 *
 * %d : integer
 *
 * %x : lower case in hexadecimal
 *
 * @param ... List of arguments
 *
 * Each arguments can be get from the stack, s+=4 will be the first argument, etc
 *
 * @return
 */
extern void printf(char* s, ...);

/**
 * @brief Set cursor position
 *
 * @param x New x position
 * @param y New y position
 * @return
 */
extern void setCursorPosition(uchar x, uchar y);

/**
 * @brief Get cursor position
 *
 * @param x pointer to store the x position
 * @param y pointer to store the x position
 *
 * @return
 */
extern void getCursorPosition(uchar* x, uchar* y);



#endif

