#include <stdio.h>
#include "const.h"

// isComputer = 0 or > 2 -> no computer
// isComputer = 1 -> player 1 is computer
void twoPlayers(int whoseTurn, int isComputer)
{
    char board[SIDE][SIDE];
    int move = 0;
    for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            board[i][j] = ' ';
        }

    }
    while(!gameWin(board) && emptyFields(board))
    {
        if (whoseTurn == PLAYER1)
        {
            printf("Player 1, enter your move (1-9):");
            scanf("%d", &move);
        
            int row = (move - 1) / SIDE;
            int column = (move - 1) % SIDE;

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
                if (gameWin(board))
                {
                    declareWinner(whoseTurn, isComputer);
                }
                else if (!emptyFields(board))
                {
                    printf("It's a tie!");
                }
                else
                {
                    whoseTurn = PLAYER2;
                }
            }
        }
        else if (whoseTurn == PLAYER2)
        {
            if (isComputer == COMPUTER1)
            {
                move = computer_move(board);
            }
            else
            {
                printf("Player 2, enter your move (1-9):");
                scanf("%d", &move);
            }
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
                if (gameWin(board))
                {
                    declareWinner(whoseTurn, isComputer);
                }
                else if (!emptyFields(board))
                {
                    printf("It's a tie!");
                }
                else
                {
                    whoseTurn = PLAYER1;
                }
            }
        }  
    }
}