
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



#ifndef TEST
int main(void)
{
    struct smallBoard bigBoard[SIDE];

    TRACE;
    initialization(bigBoard);
    TRACE;
    bigBoard[0].board[0][0] = 'C';
    bigBoard[0].board[1][0] = 'D';
    bigBoard[1].board[1][0] = 'E';
    bigBoard[1].board[2][2] = 'F';
    bigBoard[2].board[2][2] = 'G';
    bigBoard[4].board[2][2] = 'X';
    bigBoard[8].board[2][2] = 'H';
    print_bigBoard(bigBoard);
    TRACE;
}

#endif

