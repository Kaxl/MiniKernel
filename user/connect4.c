/*
 * =====================================================================================
 *
 *       Filename:  connect4.c
 *
 *    Description:  The connect 4 game
 *
 *        Version:  1.0
 *        Created:  01/11/2016 07:47:28 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rudolf Hohn, Axel Fahy
 *   Organization:  HES-SO hepia section ITI
 *
 * =====================================================================================
 */

#include "ulib.h"

#define BOARD           "connect4_board.txt"
#define BUFFER_BOARD    5000
#define CMD_POS         23,38

static void printBoard(char* buf);

void main() {

    // Init the buffer for the board
    char buffer_board[BUFFER_BOARD];

    // Load the board
    if (read_file(BOARD, buffer_board) < 0) {
        printf("Board not found");
        exit();
    }

    printBoard(buffer_board);

    for(;;) {
        setCursor(CMD_POS);
        while(1);
    }
}

static void printBoard(char* buf) {
    printf("%s", buf);
}
