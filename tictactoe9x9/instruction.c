#include <stdio.h>
#include "constants.h"


void instructions()
{
    printf("Chose a cell numbered from 1 to 9 as below and play");
    printf("\n");
    printf("\t\t\t 1 | 2 | 3 \t\t\t\n \t\t\t 4 | 5 | 6\t\t\t\n \t\t\t 7 | 8 | 9 \t\t\t\n");
    printf("\n");

    printf("Tic Tac Toe 9x9 is played in a big board where each spot is its own little 3x3 board. Player enter first value to pick which small board they will play at and then enter another number to place their X or O sign. Next, what the opponent chose will be your small board spot unless it is taken by win or draw, then player gets to pick again in which big small board wants to play.THE WINNER is the player who wins in the big board.\n");

}
#if 0
    for (int row = 0; row < INNER_SIZE; row++) {
        // For each row, display 3 inner boards horizontally
        for (int inner_row = 0; inner_row < INNER_SIZE; inner_row++) {
            for (int col = 0; col < INNER_SIZE; col++) 
            {
                // Print part of the inner board for each cell
                printf("   |   |   ");
    
                if (col < INNER_SIZE - 1) // Print column separator
                    printf("|");
            }
            printf("\n");

            if (inner_row < INNER_SIZE - 1) 
            {
                for (int col = 0; col < INNER_SIZE; col++) 
                {
                    printf("-----------");
                    if (col < INNER_SIZE - 1) // Print inner separator
                        printf("|");
                }
                printf("\n");
            }
        }

        if (row < INNER_SIZE - 1) 
        {
            for (int col = 0; col < INNER_SIZE; col++) 
            {
                printf("===========");
                if (col < INNER_SIZE - 1)
                    printf("=");
            }
            printf("\n");
        }
    }
}
#endif