
#include "constants.h"

void print_bigBoard(struct smallBoard bigBoard[SIDE])
{
   
        for (int i = 0; i < 3; i++)
        {
            int s=0;
            for (int j =0; j< 9; j++)
            {
                printf("%c", bigBoard[i].board[i][j%3]);
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
                    printf("%c", bigBoard[i].board[i-3][j%3]);
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
            for (int j =0; j< 9; j++)
            {
                printf("%c", bigBoard[i].board[i-6][j%3]);
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
    print_bigBoard(bigBoard);
    TRACE;
}

#endif

