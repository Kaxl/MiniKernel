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

volatile ushort* charPointer = FIRST_ADDR;
volatile uchar* currentPointer[2];

void initScreen() {
    //clearScreen();
    setCursorPosition(0, 1);
    //setAllBackgroundColor(0); // 0 is for black
    //setAllTextColor(15); // 15 is for white
    printCharacter(65);
}
// appeler le clear screen, positionner le curseur en (0, 0), background noir, ecriture blanche

void clearScreen() {
    int i, j;
    for (i = 0; i < SCREEN_WIDTH; i++) {
        for (j = 0; j < SCREEN_HEIGHT; j++) {
            setCursorPosition(i,j);
            printCharacter(0);
        }
    }
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

void printCharacter(uchar character) {
    //uchar* cursorPos = getCursorPosition();
    uchar* cursorPos[2];
    getCursorPosition(cursorPos);
    ushort* tmpPtr = gridToLine(cursorPos[0], cursorPos[1]); 
    //ushort* tmpPtr = gridToLine(posGrid[0], posGrid[1]); 

    *tmpPtr = *tmpPtr & (0xFF << 8);
    *tmpPtr = *tmpPtr | character;
}
// recuperer le curseur, imprimer le caractere a cette position, avancer le curseur d'une pos

void printString(uchar* string) {

}
// recuperer le curseur, appeler printCharacter

void printf() {

}

void setCursorPosition(uchar x, uchar y) {
    int pos = gridToLine(x, y);
    outb(0x3d4, 14);
    outw(0x3d5, (ushort)(pos-FIRST_ADDR >> 8)); // MSB of pos
    outb(0x3d4, 15);
    outw(0x3d5, (ushort)(pos-FIRST_ADDR & 255)); // LSB of pos
}
// convertir l'adresse 2-Dim en hexa 1-Dim puis passer dans les 3d4 et 3d5 le msb et le lsb de la position a l'aide de outb et outw

int getCursorPosition(uchar* posGrid) {
    int pos;
    outb(0x3d4, 14);
    pos = (int)(inw(0x3d5)) << 8; // MSB of pos
    outb(0x3d4, 15);
    pos = pos | (int)(inw(0x3d5)); // LSB of pos
    lineToGrid(pos*2+FIRST_ADDR, posGrid);
    return pos+FIRST_ADDR;

}
// lit les registres des registres 3d4 et 3d5 avec inb et inw les msb et lsb de la position a l'aide de inb et inw, puis convertir l'adresse hex 1-dim en position 2-Dim

int gridToLine(uchar x, uchar y) {
    // 0xBA000 + (hex)(y * 80 + x) or 753664 + (y * 80 + x)
    return FIRST_ADDR + (y * SCREEN_WIDTH + x);
}

void lineToGrid(int pos, uchar* posGrid) {
    //uchar* posGrid[2];

    // pos / 80 => le quotient c'est x, le reste c'est y
    posGrid[0] = (uchar)((pos-FIRST_ADDR) / 80);
    posGrid[1] = (uchar)((pos-FIRST_ADDR) % 80);
    
    //return posGrid;
}

