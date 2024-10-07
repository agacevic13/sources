#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <stdbool.h>


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
struct smallBoard small;
struct smallBoard bigBoard[SIDE];

struct smallBoard bigBoard[9];
void initialization(struct smallBoard bigBoard[9]);





#endif
