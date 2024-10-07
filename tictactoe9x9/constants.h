#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stdbool.h>
#include <stdio.h>


#define PLAYER1 1 
#define PLAYER2 2 
#define SIDE 9 
#define INNER_SIZE 3

//prototypes
void instructions();
struct smallBoard
{
    char board[INNER_SIZE][INNER_SIZE]; 
    char winner;
    
};

extern struct smallBoard bigBoard[SIDE];
void initialization(struct smallBoard bigBoard[SIDE]);
void print_bigBoard(struct smallBoard bigBoard[SIDE]);

#endif
