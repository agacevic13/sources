#include <stdio.h>
#include "constants.h"

struct smallBoard bigBoard[SIDE];

void initialization(struct smallBoard bigBoard[SIDE]){
    TRACE;
    for(int i = 0; i < SIDE; i++){
        TRACE;
        bigBoard[i].winner = ' ';
        bigBoard[i].active = false;
        for(int j=0; j < INNER_SIZE; j++){
            TRACE;
            for(int k=0; k<INNER_SIZE; k++){
                TRACE;
                bigBoard[i].board[j][k]= ' ';

            }
        }
    }
}


void next_table(struct smallBoard bigBoard[SIDE], int next){
             
           for(int i=0; i<SIDE; i++){
             bigBoard[i].active = false;
           }
          if(bigBoard[next-1].winner ==' '){
         bigBoard[next-1].active = true;
         
          }
          else{
            printf("Next table is completed. Choose another!");
             scanf("%d", &next);
             next_table(bigBoard, next);
          }
          printf("You are in small board %d.", next);

}


void small_win(struct smallBoard bigBoard[SIDE], int table){
     //checking rows
     for(int i=0; i<INNER_SIZE; i++){
        if(bigBoard[table].board[i][0] == bigBoard[table].board[i][1] && bigBoard[table].board[i][1] == bigBoard[table].board[i][2] ){
        if(bigBoard[table].board[i][0] == PLAYER1_SIMBOL){
            bigBoard[table].winner = PLAYER1_SIMBOL;
        }
        else {
              bigBoard[table].winner = PLAYER2_SIMBOL;
        }
        }  
     }

     //checking columns
}



#ifdef TEST 

int main(void){
// initialise();

}
#endif
