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
#define CMD_POS         38,23
#define SIZE_BOARD      7
#define GAP_ROW         6
#define GAP_LINE        2
#define FIRST_CELL_X    6
#define FIRST_CELL_Y    7
#define LAST_CELL_X     (FIRST_CELL_X+SIZE_BOARD*GAP_ROW)
#define LAST_CELL_Y     (FIRST_CELL_Y+SIZE_BOARD*GAP_LINE)
#define CURS_POS_X(x)   ((x<SIZE_BOARD)&&(x>=0)?FIRST_CELL_X+(x*GAP_ROW):LAST_CELL_X)
#define CURS_POS_Y(y)   ((y<SIZE_BOARD)&&(y>=0)?FIRST_CELL_Y+(y*GAP_LINE):LAST_CELL_Y)

static void printBoard(char* buf);
static void initBoard();

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
        initBoard();
        setCursor(CMD_POS);
        setCursor(CURS_POS_X(3), CURS_POS_Y(SIZE_BOARD-1));
        while(1);
    }
}

static void printBoard(char* buf) {
    printf("%s", buf);
}

static void initBoard() {
    for (int i = 0; i < SIZE_BOARD; i++) {
        for (int j = 0; j < SIZE_BOARD; j++) {
            setCursor(CURS_POS_X(i), CURS_POS_Y(j));
            putc(' ');
        }
    }
}
