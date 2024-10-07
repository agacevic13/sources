#ifndef CONST_H_
#define CONST_H_

#include <stdbool.h>


#define PLAYER1 1 
#define PLAYER2 2 
#define COMPUTER 3
#define SIDE 3 
#define PLAYER1_SYMBOL 'O' 
#define PLAYER2_SYMBOL 'X'
#define COMPUTER_SYMBOL 'X'
#define COMPUTER1 1
#define COMPUTER0 0
#define INNER_SIZE 3

//prototypes
void show_board(char board[SIDE][SIDE]);
void instructions();
void singlePlayer(int whoseTurn);
void twoPlayers(int whoseTurn, int isComputer);
void declareWinner(int whoseTurn, int isComputer);
bool emptyFields(char board[SIDE][SIDE]);
int gameWin(char board[SIDE][SIDE]);
void tictactoe();

bool is_empty(int move, char board[SIDE][SIDE]);
int computer_move(char board[SIDE][SIDE]);







#endif
