#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stdbool.h>
#include <stdio.h>

#if 0
#define TRACE printf("%s, #%d\n", __func__, __LINE__)
#else
#define TRACE
#endif


#define PLAYER1 1 
#define PLAYER2 2 
#define SIDE 9 
#define INNER_SIZE 3
#define PLAYER1_SIMBOL 'X'
#define PLAYER2_SIMBOL 'O'


//prototypes
void instructions();
struct smallBoard
{
    char board[INNER_SIZE][INNER_SIZE]; 
    char winner;
    bool active;
    
};
void instructions();
extern struct smallBoard bigBoard[SIDE];
void initialization(struct smallBoard bigBoard[SIDE]);
void print_bigBoard(struct smallBoard bigBoard[SIDE]);
void next_table(struct smallBoard bigBoard[SIDE], int next);
void convert(int whoseTurn);

#endif
