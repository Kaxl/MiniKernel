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
#define FIRST_ADDR_HEX 0xB8000
#define FIRST_ADDR 753664
#define CHAR_COUNT SCREEN_WIDTH*SCREEN_HEIGHT

// Functions written in controller_asm.s
extern void outb(ushort port, uchar data);
extern void outw(ushort port, ushort data);
extern uchar inb(ushort port);
extern ushort inw(ushort port);

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
// convertit l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

/**
 * @brief Get the text color
 *
 * @param x Row of the character
 * @param y Line of the character
 * @return uchar Color of the char at the position (x, y)
 */
uchar getTextColor(uchar x, uchar y);
// convertit l'adresse en offset heca 1-DIM, retourne la couleur presente dans les attributs

/**
 * @brief Set the background color of all the screen
 * 
 * @param color
 * @return
 */
void setAllBackgroundColor(uchar color);
// parcourt tous les caracters et fait setBackgroundColor

/**
 * @brief Set the background color
 *
 * @param x Row of the character
 * @param y Line of the character
 * @param color
 * @return
 */
void setBackgroundColor(uchar x, uchar y, uchar color);
// convertit l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

/**
 * @brief Get the background color
 *
 * @param x Row of the character
 * @param y Line of the character
 * @return uchar Color of the char at the position (x, y)
 */
uchar getBackgroundColor(uchar x, uchar y);
// convertir l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

/**
 * @brief Print a character
 *
 * @param character Character to print
 * @return
 */
void printCharacter(uchar character);
// recuperer le curseur, imprimer le caractere a cette position, avancer le curseur d'une pos


/**
 * @brief Print a string
 *
 * @return
 */
void printString(uchar* string);
// recuperer le curseur, appeler printCharacter

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
 * @param x Row of the cursor
 * @param y Line of the cursor
 * @return
 */
void setCursorPosition(uchar x, uchar y);
// convertir l'adresse 2-Dim en hexa 1-Dim puis passer dans les 3d4 et 3d5 le msb et le lsb de la position a l'aide de outb et outw

/**
 * @brief Get cursor position
 *
 * @return The position in an array
 */
int getCursorPosition(uchar* posGrid);
// lit les registres des registres 3d4 et 3d5 avec inb et inw les msb et lsb de la position a l'aide de inb et inw, puis convertir l'adresse hex 1-dim en position 2-Dim

/**
 * @brief Convert 2 dimensions coordinate to 1 dimension position
 *
 * @return The 1 dim position
 */
int gridToLine(uchar x, uchar y);
// 0xBA000 + (hex)(y * 80 + x) or 753664 + (y * 80 + x)

/**
 * @brief Convert 1 dimension position to 2 dimensions coordinate 
 *
 * @return The 2 dim coordinate
 */
void lineToGrid(int pos, uchar* posGrid);
// pos / 80 => le quotient c'est x, le reste c'est y

#endif

