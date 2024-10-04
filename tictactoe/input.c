#include <stdio.h>
#include <stdbool.h>

#include "const.h"

void show_board(char *[3]);
  int rowCrossed(char board[SIDE][SIDE])
    {
        for(int i=0; i<SIDE;i++)
        {
            if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
            {
                return 1;
            }
        }
        return 0;
    }
    int columnsCrossed(char board[][SIDE])
    {
        for(int i=0; i<SIDE;i++)
        {
            if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
            {
                return 1;
            }
        }
        return 0;
    }
    int diagonalsCrossed(char board[][SIDE])
    {
        if((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || 
            (board[0][2] == board[1][1] && board[1][1] == board[2][0]))
        {
            return 1;
        }

        return 0; 
    }


bool emptyFields(char board[SIDE][SIDE])
{
    for (int i = 0; i<SIDE; i++)
    {
        for (int j=0;j<SIDE;j++)
        {
            if (board[i][j] == ' ')
            return true;
        }
    }
    return false;
}

void declareWinner(whoseTurn)
{
    if (whoseTurn == PLAYER1)
    {
        printf("Player 1 wins!");
    }
    else
    {
        printf("Player 2 wins!");
    }
}

int gameWin(char board[SIDE][SIDE]) 
    { 
	    return (rowCrossed(board) || columnsCrossed(board) || diagonalsCrossed(board));
        
    }

  
void tictactoe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moves[SIDE * SIDE];
    int move = 0;

    instructions();

    for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            board[i][j] = ' ';
        }

    }

    while(!gameWin && emptyFields)
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
                    declareWinner(whoseTurn);
                }
                else
                {
                    continue;
                }
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
                if (gameWin(board))
                {
                    declareWinner(whoseTurn);
                }
                else
                {
                    continue;
                }
            }
            whoseTurn = PLAYER1;
        }  
        //printf("It's a tie!");
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