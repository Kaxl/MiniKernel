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

volatile uint charPointer = FIRST_ADDR;
volatile uchar currentPointer[2];

void initScreen() {
    clearScreen();
    //int tab[4];
    //tab[0] = 65;
    //tab[1] = 120;
    //tab[2] = 101;
    //tab[3] = 108;

    //for (int i = 0; i < 4; i++) {
    //    setCursorPosition(0, i);
    //    setTextColor(0, i, i + 1);
    //    printCharacter(tab[i]);
    //    setCursorPosition(i, 0);
    //    setTextColor(i, 0, i + 2);
    //    printCharacter(tab[i]);
    //}
    //setAllBackgroundColor(0); // 0 is for black
    //setAllTextColor(15); // 15 is for white
    setCursorPosition(5, 5);
    setTextColor(5, 5, 1);
    printCharacter(65);
    setCursorPosition(1, 0);
    setTextColor(1, 0, 1);
    printCharacter(66);
    //setCursorPosition(0, 2);
    //printCharacter(67);
    //setCursorPosition(0, 3);
    //printCharacter(68);
    //setCursorPosition(15, 40);
    //printCharacter(67);
}
// appeler le clear screen, positionner le curseur en (0, 0), background noir, ecriture blanche

void clearScreen() {
    int i, j;
    for (i = 0; i < SCREEN_WIDTH; i++) {
        for (j = 0; j < SCREEN_HEIGHT; j++) {
            setTextColor(i, j, 15);
            //setBackgroundColor(i, j, 0);
            setBackgroundColor(i, j, 1);
            setCursorPosition(i,j);
            //printCharacter(0);
            printCharacter(65);
        }
    }
}
// il nettoie juste les valeurs ascii des caracters mais laisse les proprietes des caracteres (parcourir tous les caracteres) donc ne modifie ni le backgroud ni le font-color

void setAllTextColor(uchar color) {
    // Change text color of all screen
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            setTextgroundColor(i, j, color);
        }
    }
}

void setTextColor(uchar x, uchar y, uchar color) {
    // Get the address of the position to change
    int* pos = (int *)(gridToLine(x, y) + FIRST_ADDR);

    // Set bits [8..11] to 0
    *pos = *pos & ~(0xF00);
    // Set the color of text in bits [8..11]
    *pos = *pos | (color << 8);
}

uchar getTextColor(uchar x, uchar y) {
}
// convertit l'adresse en offset heca 1-DIM, retourne la couleur presente dans les attributs

void setAllBackgroundColor(uchar color) {
    // Change background color of all screen
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            setBackgroundColor(i, j, color);
        }
    }
}

void setBackgroundColor(uchar x, uchar y, uchar color) {
    // Get the address of the position to change
    int* pos = (int *)(gridToLine(x, y) + FIRST_ADDR);

    // Set bits [12..15] to 0
    *pos = *pos & ~(0xF000);
    // Set the color of text in bits [12..15]
    *pos = *pos | (color << 12);

}

uchar getBackgroundColor(uchar x, uchar y) {

}
// convertir l'adresse en offset hexa 1-DIM, applique la couleur en gardant la valeur ascii

void printCharacter(uchar character) {
    //uchar* cursorPos = getCursorPosition();
    //uchar cursorPos[2];
    int* cursorPos = (int *)getCursorPosition();
    //ushort* tmpPtr = gridToLine(cursorPos[0], cursorPos[1]);
    //ushort* tmpPtr = gridToLine(posGrid[0], posGrid[1]);

    //*tmpPtr = *tmpPtr & (0xFF << 8);
    //*tmpPtr = *tmpPtr | character;
    *cursorPos = *cursorPos & (0xFF << 8);
    *cursorPos = *cursorPos | character;
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
    outw(0x3d5, (ushort)(pos >> 8)); // MSB of pos
    outb(0x3d4, 15);
    outw(0x3d5, (ushort)(pos & 255)); // LSB of pos
}
// convertir l'adresse 2-Dim en hexa 1-Dim puis passer dans les 3d4 et 3d5 le msb et le lsb de la position a l'aide de outb et outw

// KO !!!!!!!!!
int getCursorPosition() {
    int pos;
    outb(0x3d4, 14);
    pos = (int)(inw(0x3d5)) << 8; // MSB of pos
    outb(0x3d4, 15);
    pos = pos | (int)(inw(0x3d5)); // LSB of pos
    //uchar posGrid[2];
    //posGrid = lineToGrid(pos * 2 + FIRST_ADDR);
    //return pos + FIRST_ADDR;
    return pos + FIRST_ADDR;

}
// lit les registres des registres 3d4 et 3d5 avec inb et inw les msb et lsb de la position a l'aide de inb et inw, puis convertir l'adresse hex 1-dim en position 2-Dim

int gridToLine(uchar x, uchar y) {
    // We need to multiply by 2 because each character is on 2 bytes
    return y * (SCREEN_WIDTH * 2) + (x * 2);
}

uchar* lineToGrid(int pos) {
    static uchar posGrid[2];

    // pos / 80 => le quotient c'est x, le reste c'est y
    posGrid[0] = (uchar)((pos-FIRST_ADDR) / 80);
    posGrid[1] = (uchar)((pos-FIRST_ADDR) % 80);

    return posGrid;
}

