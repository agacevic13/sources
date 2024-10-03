#include <stdio.h>

#include "const.h"

void show_board(char *[3]);

void tictactoe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];
    int move = 0;
    for(int i=0; i<SIDE; i++){
        for(int j=0; j<SIDE; j++){
            board[i][j]=' ';
        }

    }

    instructions();
    while(1)
    {
        if (whoseTurn == PLAYER1)
        {
            printf("Player 1, enter your move (1-9):");
            scanf("%d", &move);
            int row = (move - 1) / SIDE;
            int column = (move - 1) % SIDE;
            //board[row][column] = PLAYER1_SYMBOL;
            if (move < 1 || move > 9)
            {
                printf("Invalid input, please try again.\n");
                continue;
            }
            else if (board[row][column] != ' ')
            {
                printf("Field already taked. Try another.");
                continue; 
            }
            else
            {
                board[row][column] = PLAYER1_SYMBOL;
                show_board(board);
            }
            whoseTurn = PLAYER2;
        }
        else if (whoseTurn == PLAYER2)
        {
            printf("Player 2, enter your move (1-9):");
            scanf("%d", &move);
            int row = (move - 1) / SIDE;
            int column = (move - 1) % SIDE;
            if (move < 1 || move > 9)
            {
                printf("Invalid input, please try again.");
                continue;
            }
            else if (board[row][column] != ' ')
            {
                printf("Field already taked. Try another.");
                continue; 
            }
            else
            {
                board[row][column] = PLAYER2_SYMBOL;
                show_board(board);
            }
            whoseTurn = PLAYER1;
        }
    }
}

int main(void)
{
    tictactoe(1);
}

#ifdef TESTS
void show_board(char *[3])
{
     
}
int main(void)
{
    tictactoe(1);
}
#endif