#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "const.h"
#include <stdbool.h>

bool  is_empty(int move, char board[SIDE][SIDE])
{
int row = (move-1)/SIDE;
int column = (move-1)%SIDE;
if(board[row][column]==' '){
    return true;
}else{
    return false;
}
}

int computer_move(char board[SIDE][SIDE]){
   
      static int initialized = 0;
   if (!initialized) {
       srand(time(NULL));  
       initialized = 1;     
   }

 while(1){
     int move = (rand()%(SIDE*SIDE))+1;
     if(is_empty(move, board)){
        return move;
     }
    }


}


#ifdef TEST

void main(void){
    char board[SIDE][SIDE];
    for(int i=0; i<SIDE; i++){
        for(int j=0; j<SIDE; j++){
       board[i][j]=' ';
        }
    }

    printf("%d\n", computer_move(board));
}
 

#endif