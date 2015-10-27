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

/**
 * @brief Initialization of the screen
 *
 * Clear the screen and set the cursor's position at top left.
 *
 * @return
 */
void initScreen();

/**
 * @brief Clear the screen
 *
 * @return
 */
void clearScreen();

/**
 * @brief Set the text color
 *
 * @return
 */
void setTextColor();

/**
 * @brief Get the text color
 *
 * @return
 */
void getTextColor();

/**
 * @brief Set the background color
 *
 * @return
 */
void setBackgroundColor();

/**
 * @brief Get the background color
 *
 * @return
 */
void getBackgroundColor();

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

#endif

