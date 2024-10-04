#ifndef CONST_H_
#define CONST_H_

#include <stdbool.h>


#define PLAYER1 1 
#define PLAYER2 2 
#define COMPUTER 1
#define PLAYER 2
#define SIDE 3 
#define PLAYER1_SYMBOL 'O' 
#define PLAYER2_SYMBOL 'X'
#define COMPUTER_SYMBOL 'X'
#define PLAYER_SYMBOL 'O'

//prototypes
void show_board(char board[SIDE][SIDE]);
void instructions();
void singlePlayer(int whoseTurn);
void twoPlayers(int whoseTurn);
void declareWinner(int whoseTurn);
bool emptyFields(char board[SIDE][SIDE]);
int gameWin(char board[SIDE][SIDE]);
void tictactoe();

#endif
