
#include "constants.h"


// printing small board 
void print_bigBoard(struct smallBoard bigBoard[SIDE])
{
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j< INNER_SIZE; j++)
        {
            for (int k = 0; k< 3; k++)
            {
                printf("|");
                printf("%c ", bigBoard[i * 3 + k].board[j][k]);
            }
            printf("|\n");
        }
        printf("==============\n");
    }

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

