#include <stdio.h>
#include "const.h"

#define SIZE SIDE

void instructions(){
    printf("Chose a cell numbered from 1 to 9 as below and play");
   printf("\n");
    printf("\t\t\t 1 | 2 | 3 \t\t\t\n \t\t\t 4 | 5 | 6\t\t\t\n \t\t\t 7 | 8 | 9 \t\t\t\n");
    printf("\n");
}

void show_board(char board[SIZE][SIZE])
{
   
  
     printf("\n\t\t\t %c | %c | %c \t\t\t\n \t\t\t %c | %c | %c\t\t\t\n \t\t\t %c | %c | %c \t\t\t\n", board[0][0], board[0][1], board[0][2],board[1][0], board[1][1],board[1][2],board[2][0],board[2][1],board[2][2]);
   
}

#ifdef TESTS
int main(void)
{
   instructions();

   show_board("abcdefghi");
}
#endif
