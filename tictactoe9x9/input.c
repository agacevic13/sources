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
bool emptyFields(struct smallBoard bigBoard[SIDE], int table)
{
    for (int i = 0; i<INNER_SIZE; i++)
    {
        for (int j=0;j<INNER_SIZE;j++)
        {
            if (bigBoard[table].board[i][j] == ' ')
            return true;
        }
    }
    return false;
}

void next_table(struct smallBoard bigBoard[SIDE], int next){
             
           for(int i=0; i<SIDE; i++){
             bigBoard[i].active = false;
           }
          if(bigBoard[next-1].winner ==' '){
         bigBoard[next-1].active = true;
         
          }
          else if (bigBoard[next-1].winner == PLAYER1_SIMBOL || bigBoard[next-1].winner == PLAYER2_SIMBOL)
          {
            if(bigBoard[next-1].winner == PLAYER1_SIMBOL)
            {
                printf("Player 1 wins this small board!\n");
            }
            else
            {
            printf("Player 2 wins this small board!\n");

            }
            printf("Choose another:");
             scanf("%d", &next);
             next_table(bigBoard, next);
          }
          else
          {
            printf("It's a tie! Table is completed. Choose another!");
             scanf("%d", &next);
             next_table(bigBoard, next);
          }
          printf("You are in small board %d.\n", next);

}


void small_win(struct smallBoard bigBoard[SIDE], int table){
     //checking rows
     for(int i=0; i<INNER_SIZE; i++){
        if(bigBoard[table].board[i][0] == bigBoard[table].board[i][1] && bigBoard[table].board[i][1] == bigBoard[table].board[i][2] &&   bigBoard[table].board[i][2]!=' '){
        if(bigBoard[table].board[i][0] == PLAYER1_SIMBOL){
            bigBoard[table].winner = PLAYER1_SIMBOL;
        }
        else {
              bigBoard[table].winner = PLAYER2_SIMBOL;
        }
        }  
     }

     //checking columns

     for(int i=0; i<INNER_SIZE; i++){
        if(bigBoard[table].board[0][i] == bigBoard[table].board[1][i] && bigBoard[table].board[1][i] == bigBoard[table].board[2][i] &&  bigBoard[table].board[2][i]!=' '){
            if(bigBoard[table].board[0][i] == PLAYER1_SIMBOL){
                bigBoard[table].winner = PLAYER1_SIMBOL;
            }
            else {
                bigBoard[table].winner = PLAYER2_SIMBOL;
            }
        }
     }


     //checking diagonals
    if(bigBoard[table].board[1][1] == bigBoard[table].board[2][2] && bigBoard[table].board[2][2] == bigBoard[table].board[0][0] && bigBoard[table].board[0][0]!=' '){
       if(bigBoard[table].board[0][0] == PLAYER1_SIMBOL){
                bigBoard[table].winner = PLAYER1_SIMBOL;
            }
            else {
                bigBoard[table].winner = PLAYER2_SIMBOL;
            }
    }
     if(bigBoard[table].board[0][2] == bigBoard[table].board[1][1] && bigBoard[table].board[2][0] == bigBoard[table].board[1][1] && bigBoard[table].board[1][1]!=' '){
       if(bigBoard[table].board[1][1] == PLAYER1_SIMBOL){
                bigBoard[table].winner = PLAYER1_SIMBOL;
            }
            else {
                bigBoard[table].winner = PLAYER2_SIMBOL;
            }
    }
    // check tie
        if(emptyFields(bigBoard, table) == false){
            bigBoard[table].winner='/';
        }
}

bool bigWinner(struct smallBoard bigBoard[SIDE] ){
      for(int i=0; i<INNER_SIZE*INNER_SIZE; i+=INNER_SIZE){
        
        if(bigBoard[i].winner==bigBoard[i+1].winner && bigBoard[i+1].winner==bigBoard[i+2].winner && bigBoard[i+2].winner != ' '){
            return true;
        }
      }
      //check columns
    for(int i=0; i<INNER_SIZE; i++){
        if(bigBoard[i].winner==bigBoard[i+3].winner && bigBoard[i+3].winner==bigBoard[i+6].winner && bigBoard[i].winner != ' '){
            return true;
        }
    }

    //diagonals

    if(bigBoard[0].winner==bigBoard[4].winner && bigBoard[4].winner==bigBoard[8].winner && bigBoard[4].winner!=' '){
        return true;

    }

    if(bigBoard[2].winner==bigBoard[4].winner && bigBoard[4].winner==bigBoard[6].winner && bigBoard[4].winner!=' '){
        return true;

    }
      return false;


}


char whoIsWinner(struct smallBoard bigBoard[SIDE]){
    for(int i=0; i<INNER_SIZE*INNER_SIZE; i+=INNER_SIZE){
        
        if(bigBoard[i].winner==bigBoard[i+1].winner && bigBoard[i+1].winner==bigBoard[i+2].winner && bigBoard[i+2].winner != ' '){
            return bigBoard[i].winner;
        }
      }
      //check columns
    for(int i=0; i<INNER_SIZE; i++){
        if(bigBoard[i].winner==bigBoard[i+3].winner && bigBoard[i+3].winner==bigBoard[i+6].winner && bigBoard[i].winner != ' '){
            return bigBoard[i].winner;
        }
    }

    //diagonals

    if(bigBoard[0].winner==bigBoard[4].winner && bigBoard[4].winner==bigBoard[8].winner && bigBoard[4].winner!=' '){
        return bigBoard[0].winner;

    }

    if(bigBoard[2].winner==bigBoard[4].winner && bigBoard[4].winner==bigBoard[6].winner && bigBoard[4].winner!=' '){
        return bigBoard[2].winner;

    }
      return '/';
}


#ifdef TEST 

int main(void){
// initialise();

}
#endif
