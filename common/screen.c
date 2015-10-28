/*
 * =====================================================================================
 *
 *       Filename:  screen.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/16/2015 11:21:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Axel Fahy, Rudolf Hohn
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "screen.h"

void initScreen() {

}
// appeler le clear screen, positionner le curseur en (0, 0), background noir, ecriture blanche

void clearScreen() {

}
// il nettoie juste les valeurs ascii des caracters mais laisse les proprietes des caracteres (parcourir tous les caracteres) donc ne modifie ni le backgroud ni le font-color

void setAllTextColor(uchar color) {

}
// parcourt tous les caracteres et fait setTextColor

void setTextColor(uchar x, uchar y, uchar color) {

}
// convertit l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

uchar getTextColor(uchar x, uchar y) {
    
}
// convertit l'adresse en offset heca 1-DIM, retourne la couleur presente dans les attributs

void setAllBackgroundColor(uchar color) {
    
}
// parcourt tous les caracters et fait setBackgroundColor

void setBackgroundColor(uchar x, uchar y, uchar color) {

}
// convertit l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

uchar getBackgroundColor(uchar x, uchar y) {

}
// convertir l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

void printCharacter(char character) {

}
// recuperer le curseur, imprimer le caractere a cette position, avancer le curseur d'une pos

void printString(char* string) {

}
// recuperer le curseur, appeler printCharacter

void printf() {

}

void setCursorPosition(uchar x, uchar y) {

}
// convertir l'adresse 2-Dim en hexa 1-Dim puis passer dans les 3d4 et 3d5 le msb et le lsb de la position a l'aide de outb et outw

uchar* getCursorPosition() {

}
// lit les registres des registres 3d4 et 3d5 avec inb et inw les msb et lsb de la position a l'aide de inb et inw, puis convertir l'adresse hex 1-dim en position 2-Dim

int gridToLine(uchar x, uchar y) {

}
// 0xBA000 + (hex)(y * 80 + x) or 753664 + (y * 80 + x)

uchar* lineToGrid(int pos) {

}
// pos / 80 => le quotient c'est x, le reste c'est y

