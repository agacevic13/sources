#include <stdio.h>
#include "constants.h"

void initialization(struct smallBoard bigBoard[9]){
   for(int i = 0; i <9; i++){
    bigBoard[i].winner = ' ';

    for(int j=0; j<9; i++){
        for(int k=0; k<9; k++){
            bigBoard[i].board[j][k]= ' ';

        }
    }
   }
}




#ifdef TEST 

int main(void){
   // initialise();

}


#endif







