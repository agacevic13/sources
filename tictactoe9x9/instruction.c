#include <stdio.h>
#include "constants.h"

#define SIZE SIDE

void instructions()
{
    printf("Chose a cell numbered from 1 to 9 as below and play");
    printf("\n");
    printf("\t\t\t 1 | 2 | 3 \t\t\t\n \t\t\t 4 | 5 | 6\t\t\t\n \t\t\t 7 | 8 | 9 \t\t\t\n");
    printf("\n");


    for (int row = 0; row < SIZE; row++) {
        // For each row, display 3 inner boards horizontally
        for (int inner_row = 0; inner_row < INNER_SIZE; inner_row++) {
            for (int col = 0; col < SIZE; col++) 
            {
                // Print part of the inner board for each cell
                printf("   |   |   ");
    
                if (col < SIZE - 1) // Print column separator
                    printf("|");
            }
            printf("\n");

            if (inner_row < INNER_SIZE - 1) 
            {
                for (int col = 0; col < SIZE; col++) 
                {
                    printf("-----------");
                    if (col < SIZE - 1) // Print inner separator
                        printf("|");
                }
                printf("\n");
            }
        }

        if (row < SIZE - 1) 
        {
            for (int col = 0; col < SIZE; col++) 
            {
                printf("===========");
                if (col < SIZE - 1)
                    printf("=");
            }
            printf("\n");
        }
    }


}

void show_board(char board[SIZE][SIZE])
{
   
  
     printf("\n\t\t\t %d | %c | %c \t\t\t\n \t\t\t %c | %c | %c\t\t\t\n \t\t\t %c | %c | %c \t\t\t\n", board[0][0], board[0][1], board[0][2],board[1][0], board[1][1],board[1][2],board[2][0],board[2][1],board[2][2]);
   
}

#ifdef TESTS
int main(void)
{
   instructions();

   show_board("abcdefghi");
}
#endif
