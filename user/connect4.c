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

#define NB_PLAYER       2
#define BOARD           "connect4_board.txt"
#define BUFFER_BOARD    5000
#define CMD_POS         38,23
#define SCORE_1_POS     58,14
#define SCORE_2_POS     70,14
#define PLAYER_ROUND    11,23
#define SIZE_BOARD      7
#define GAP_ROW         6
#define GAP_LINE        2
#define FIRST_CELL_X    6
#define FIRST_CELL_Y    7
#define LAST_CELL_X     (FIRST_CELL_X+(SIZE_BOARD-1)*GAP_ROW)
#define LAST_CELL_Y     (FIRST_CELL_Y+(SIZE_BOARD-1)*GAP_LINE)
#define CURS_POS_X(x)   ((x<SIZE_BOARD)&&(x>=0)?FIRST_CELL_X+(x*GAP_ROW):LAST_CELL_X)
#define CURS_POS_Y(y)   ((y<SIZE_BOARD)&&(y>=0)?FIRST_CELL_Y+(y*GAP_LINE):LAST_CELL_Y)
#define PLAYER_TOKEN(x) ".OX"[x]
#define CTOI(x)         (int)(x-'0')
#define GOOD_NB(x)      (x>=0)&&(x<SIZE_BOARD)

static void printBoard(char* buf);
static void cleanBoard(char* board);
static void cleanScore(char* score);
static void printScore(char* score);
static void setPlayer(int i);

void main() {

    // Board play
    char board[SIZE_BOARD*SIZE_BOARD];

    // Score of players
    char score[NB_PLAYER];

    // Init the buffer for the board
    char buffer_board[BUFFER_BOARD];

    // Load the board
    if (read_file(BOARD, buffer_board) < 0) {
        printf("Board not found");
        exit();
    }

    // Print the board
    printBoard(buffer_board);

    // Clean the board
    cleanBoard(board);

    // Clean the score
    cleanScore(score);

    // The first player plays
    int player = 1;
    setPlayer(player);

    // Command of players
    char c;

    // Winning boolean
    char w = 0;

    for(;;) {
        setCursor(CMD_POS);

        // Error listening
        if ((c = getc()) < 0) continue;

        // Player leaves the game
        if (c == 'q') {
            printf("\n");
            exit();
        }

        // Player restart the game
        else if (c == 'r') {
            w = 0;
            cleanBoard(board);
        }

        // Player plays
        else if (GOOD_NB(CTOI(c)) && (w == 0)) {
            for (int i = SIZE_BOARD-1; i >= 0; i--) {
                if (board[CTOI(c)+i*SIZE_BOARD] == 0) {
                    board[CTOI(c)+i*SIZE_BOARD] = player;
                    setCursor(CURS_POS_X(CTOI(c)), CURS_POS_Y(i));
                    putc(PLAYER_TOKEN(player));
                    player = (player==1?2:1);
                    break;
                }
            }


            // Win detection
            //checks horizontal win
            for(int i = 0; i < SIZE_BOARD; i++)
                for(int j = 0; j < SIZE_BOARD-3; j++)
                    if(board[i*SIZE_BOARD+j] != 0 && board[i*SIZE_BOARD+j]==board[i*SIZE_BOARD+j+1] && board[i*SIZE_BOARD+j]==board[i*SIZE_BOARD+j+2] && board[i*SIZE_BOARD+j]==board[i*SIZE_BOARD+j+3]) {
                        w++;
                        score[player-1]++;
                    }


            //checks vertical win
            for(int i = 0; i < SIZE_BOARD - 3; i++)
                for(int j = 0; j < SIZE_BOARD; j++)
                    if(board[i*SIZE_BOARD+j] != 0 && board[i*SIZE_BOARD+j]==board[(i+1)*SIZE_BOARD+j] && board[i*SIZE_BOARD+j]==board[(i+2)*SIZE_BOARD+j] && board[i*SIZE_BOARD+j]==board[(i+3)*SIZE_BOARD+j]) {
                        w++;
                        score[player-1]++;
                    }

            //checks rigth diagonal win
            // for(int i = 0; i < SIZE_BOARD - 3; i++)
            //     for(int j = 0; j < SIZE_BOARD; j++)
            //         if(board[i][j] != 0 && board[i][j]==board[i+1][j+1] && board[i][j]==board[i+2][j+2] && board[i][j]==board[i+3][j+3]) {
            //             w++;
            //             score[player-1]++;
            //         }
            //
            // //checks left diagonal win
            // for(int i = 0; i < SIZE_BOARD - 3; i++)
            //     for(int j = 0; j < SIZE_BOARD; j++)
            //         if(board[i][j] != 0 && board[i][j]==board[i+1][j-1] && board[i][j]==board[i+2][j-2] && board[i][j]==board[i+3][j-3]) {
            //             w++;
            //             score[player-1]++;
            //         }
        }
        
        if (w == 1) printScore(score);
    }
}

static void printBoard(char* buf) {
    printf("%s", buf);
}

static void cleanBoard(char* board) {
    for (int i = 0; i < SIZE_BOARD; i++) {
        for (int j = 0; j < SIZE_BOARD; j++) {
            setCursor(CURS_POS_X(i), CURS_POS_Y(j));
            putc(' ');
            board[j*SIZE_BOARD+i] = 0;
        }
    }
}

static void cleanScore(char* score) {
    setCursor(SCORE_1_POS);
    putc('0');
    setCursor(SCORE_2_POS);
    putc('0');
    score[0] = 0;
    score[1] = 0;
}

static void printScore(char* score) {
    setCursor(SCORE_1_POS);
    printf("%d", score[0]);
    setCursor(SCORE_2_POS);
    printf("%d", score[1]);
}

static void setPlayer(int i) {
    setCursor(PLAYER_ROUND);
    printf("%d",i);
}
