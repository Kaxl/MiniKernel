/*
 * =====================================================================================
 *
 *       Filename:  screen.h
 *
 *    Description:
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

#include "types.h"
#include "colors.h"

#define SCREEN_WIDTH    80
#define SCREEN_HEIGHT   25
#define FIRST_ADDR_HEX  0xB8000
#define FIRST_ADDR      753664
#define LAST_ADDR       FIRST_ADDR + SCREEN_WIDTH * SCREEN_HEIGHT * 2 - 2
#define CHAR_COUNT      SCREEN_WIDTH * SCREEN_HEIGHT

// Functions written in controller_asm.s
extern void outb(ushort port, uchar data);
extern void outw(ushort port, ushort data);
extern uchar inb(ushort port);
extern ushort inw(ushort port);


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
void initScreen();

/**
 * @brief Clear the screen
 *
 * Clear the screen but keep the properties.
 *
 * @return
 */
void clearScreen();

/**
 * @brief Set the text color of all the screen
 *
 * @paramn color
 * @return
 */
void setAllTextColor(uchar color);
// parcourt tous les caracteres et fait setTextColor

/**
 * @brief Set the text color
 *
 * All characters written after this call will be with
 * this new color.
 *
 * @param color Color to set
 * @return
 */
void setTextColor(uchar color);

/**
 * @brief Get the text color
 *
 * @return The current color
 */
uchar getTextColor();

/**
 * @brief Set the background color of all the screen
 *
 * @param color Color to set
 * @return
 */
void setAllBackgroundColor(uchar color);

/**
 * @brief Set the background color
 *
 * All background of characters written after this call will be with
 * this new color.
 *
 * @param color
 * @return
 */
void setBackgroundColor(uchar color);

/**
 * @brief Get the background color
 *
 * @return The current background color
 */
uchar getBackgroundColor();

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
void printCharacter(uchar character);


/**
 * @brief Print a string
 *
 * @return
 */
void printString(char* string);

/**
 * @brief Printf function
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
 * @return
 */
void printf();

/**
 * @brief Set cursor position
 *
 * @param x New x position
 * @param y New y position
 * @return
 */
void setCursorPosition(uchar x, uchar y);

/**
 * @brief Get cursor position
 *
 * @param x pointer to store the x position
 * @param y pointer to store the x position
 *
 * @return
 */
void getCursorPosition(uchar* x, uchar* y);

/**
 * @brief Convert 2 dimensions coordinate to 1 dimension position
 *
 * @return The 1 dim position
 */
ushort gridToLine(uchar x, uchar y);

/**
 * @brief Convert 1 dimension position to 2 dimensions coordinate
 *
 * @return The 2 dim coordinate
 */
void lineToGrid(ushort pos, uchar* x, uchar* y);

#endif

