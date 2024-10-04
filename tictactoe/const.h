#ifndef CONST_H_
#define CONST_H_

#define PLAYER1 1 
#define PLAYER2 2 
#define SIDE 3 
#define PLAYER1_SYMBOL 'O' 
#define PLAYER2_SYMBOL 'X'

bool  is_empty(int move, char board[SIDE][SIDE]);
int computer_move(char board[SIDE][SIDE]);







#endif
