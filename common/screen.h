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

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define FIRST_ADDR 0xB8000
#define CHAR_COUNT SCREEN_WIDTH*SCREEN_HEIGHT

/**
 * @brief Initialization of the screen
 *
 * Clear the screen and set the cursor's position at top left.
 *
 * @return
 */
void initScreen();
// appeler le clear screen, positionner le curseur en (0, 0), background noir, ecriture blanche

/**
 * @brief Clear the screen
 *
 * @return
 */
void clearScreen();
// il nettoie juste les valeurs ascii des caracters mais laisse les proprietes des caracteres (parcourir tous les caracteres) donc ne modifie ni le backgroud ni le font-color

/**
 * @brief Set the text color of all the screen
 *
 * @paramn color
 * @return
 */
void setAllTextColor(uchar color);
// parcourt tous les caracteres et fait setTextColor

/**
 * @brief Set the text color at position (x, y)
 *
 * @param x Row of the character
 * @param y Line of the character
 * @param color
 * @return
 */
void setTextColor(uchar x, uchar y, uchar color);
// convertit l'adrese en offset hexa 1-DIM, 

/**
 * @brief Get the text color
 *
 * @return uchar Color of the char at the position (x, y)
 */
uchar getTextColor(uchar x, uchar y);

/**
 * @brief Set the background color of all the screen
 *
 * @return
 */
void setAllBackgroundColor();

/**
 * @brief Set the background color
 *
 * @return
 */
void setBackgroundColor(uchar x, uchar y);

/**
 * @brief Get the background color
 *
 * @return
 */
void getBackgroundColor(uchar x, uchar y);

/**
 * @brief Print a character
 *
 * @return
 */
void printCharacter();

/**
 * @brief Print a string
 *
 * @return
 */
void printString();

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
 * @return
 */
void setCursorPosition();

/**
 * @brief Get cursor position
 *
 * @return
 */
void getCursorPosition();

/**
 * @brief Convert 2 dimensions coordinate to 1 dimension position
 *
 * @return ushort The 1 dim position
 */
ushort gridToLine(uchar x, uchar y);

#endif

