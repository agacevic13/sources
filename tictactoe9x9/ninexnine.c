
#include "constants.h"

void print_bigBoard(struct smallBoard bigBoard[SIDE])
{
        for (int i = 0; i < 3; i++)
        {
            int s=0;
            for (int j =0; j< 9; j++)
            {
                printf("%c", bigBoard[j / 3].board[i][j % 3]);
                if (s <2)
                {
                  printf("|"); 
                }
                s++;
                if(s==3){
                    printf("\t");
                    s=0;
                }
            }
            printf("\n");
        }
        //printf("\n");
        printf("\n\n");
        for (int i = 3; i < 6; i++)
        {
            int s=0;
            for (int j =0; j< 9; j++)
            {
                    printf("%c", bigBoard[3 + j / 3].board[i-3][j % 3]);
                    if (s <2)
                    {
                    printf("|"); 
                    }
                    s++;
                    if(s==3){
                    printf("\t");
                    s=0;
                    }
            }
            printf("\n");
        }
        //printf("\n");
        printf("\n\n");
        for (int i = 6; i < 9; i++)
        {
            int s=0;
            for (int j = 0; j< 9; j++)
            {
                printf("%c", bigBoard[6 + j / 3].board[i-6][j % 3]);
                if (s <2)
                {
                  printf("|"); 
                }
                s++;
                if(s==3){
                    printf("\t");
                    s=0;
                }
            }
            printf("\n");
        }
        //printf("\n");
        printf("\n\n");
    }
#if 1
void convert(int whoseTurn)
{
    int move;
    int smallmove;
    printf("Input a number 1-9 in which small board you want to start? ");
    scanf("%d",&move);
    int bigmove = move -1;
    while (bigWinner(bigBoard) == false)
    {
        if (whoseTurn == PLAYER1)
        {
            printf("Player 1, input a number 1-9, where you want to place your symbol? ");
            scanf("%d",&smallmove);
            int row = (smallmove - 1) / INNER_SIZE;
            int column = (smallmove - 1) % INNER_SIZE;
            if (smallmove < 1 || smallmove > 9)
            {
                printf("Invalid input, please try again.\n");
                continue;
            }
            else if (bigBoard[bigmove].board[row][column] != ' ')
            {
                printf("Field already taked. Try another.\n");
                continue; 
            }
            else
            {
                bigBoard[bigmove].board[row][column] = PLAYER1_SIMBOL;
                print_bigBoard(bigBoard);
                //check win
                small_win(bigBoard, bigmove);
                if (bigWinner(bigBoard) == true)
                {
                    //printf("%c", whoIsWinner(bigBoard));
                    char win = whoIsWinner(bigBoard);
                    if(win == 'X')
                    {
                        printf("PLAYER 1 WINS!");
                    }
                    else if (win == 'O')
                    {
                        printf("PLAYER 2 WINS!");
                    }
                    else{
                        printf("IT'S A TIE!");
                    }
                }
                else
                {
                    next_table(bigBoard, smallmove);
                    whoseTurn = PLAYER2; 
                    for (int i = 0; i < SIDE; i++)
                    {
                        if (bigBoard[i].active == true)
                        {
                            bigmove = i;
                        }
                    
                    }
                
                }
            }

        }
        else if(whoseTurn == PLAYER2)
        {
            printf("Player 2, input a number 1-9, where you want to place your symbol? ");
            scanf("%d",&smallmove);
            int row = (smallmove - 1) / INNER_SIZE;
            int column = (smallmove - 1) % INNER_SIZE;
            if (smallmove < 1 || smallmove > 9)
            {
                printf("Invalid input, please try again.\n");
                continue;
            }
            else if (bigBoard[bigmove].board[row][column] != ' ')
            {
                printf("Field already taked. Try another.\n");
                continue; 
            }
            else
            {
                bigBoard[bigmove].board[row][column] = PLAYER2_SIMBOL;
                print_bigBoard(bigBoard);
                //check win
                small_win(bigBoard, bigmove);
                if (bigWinner(bigBoard) == true)
                {
                    //("%c", whoIsWinner(bigBoard));
                    char win = whoIsWinner(bigBoard);
                    if(win == 'X')
                    {
                        printf("PLAYER 1 WINS!");
                    }
                    else if (win == 'O')
                    {
                        printf("PLAYER 2 WINS!");
                    }
                    else{
                        printf("IT'S A TIE!");
                    }
                }
                else
                {
                    next_table(bigBoard, smallmove);
                    whoseTurn = PLAYER1; 
                    for (int i = 0; i < SIDE; i++)
                    {
                        if (bigBoard[i].active == true)
                        {
                            bigmove = i;
                        }
                    
                    }
                
                }
            }
        }

    }
}

#endif
#ifndef TEST
int main(void)
{
    instructions();
    // TRACE;
     initialization(bigBoard);
    // TRACE;
    convert(1);    
    // TRACE;

}

#endif

