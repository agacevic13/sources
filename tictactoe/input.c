#include <stdio.h>
#include <stdbool.h>

#include "const.h"

int rowCrossed(char board[SIDE][SIDE])
{
    for(int i=0; i<SIDE;i++)
    {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] != ' ')
        {
            return 1;
        }
    }
    return 0;
}
int columnsCrossed(char board[SIDE][SIDE])
{
    for(int i=0; i<SIDE;i++)
    {
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] != ' ')
        {
            return 1;
        }
    }
    return 0;
}
int diagonalsCrossed(char board[SIDE][SIDE])
{
    if((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] != ' ') || 
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[2][0] != ' '))
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

void declareWinner(int whoseTurn)
{
    if (whoseTurn == PLAYER1)
    {
        printf("Player 1 wins!");
    }
    else if (whoseTurn == PLAYER2)
    {
        printf("Player 2 wins!");
    }
    else if (whoseTurn == COMPUTER)
    {
        printf("Computer wins!");
    }
    else
    {
        printf("Player(YOU) win!");
    }
    
}

int gameWin(char board[SIDE][SIDE]) 
    { 
	    return (rowCrossed(board) || columnsCrossed(board) || diagonalsCrossed(board));
        
    }

void tictactoe()
{
    int players = 0;
    printf("How many players (1 or 2)?\n");
    scanf("%d", &players);
    if (players == 1)
    {
        int turn = 0;
        printf("Who do you want to start first (1 for computer or 2 for player)?\n");
        scanf("%d", &turn);
        if(turn == 1)
        {
            singlePlayer(1);
        }
        else
        {
            singlePlayer(2);
        }
    }
    else if (players == 2)
    {
            twoPlayers(1);
    }
    
}


#ifdef TESTS
void show_board(char board[SIDE][SIDE])
{
     
}
int main(void)
{
    tictactoe(0);
}
#endif