#include <stdio.h>
#include "constants.h"

struct smallBoard bigBoard[SIDE];
void initialization(struct smallBoard bigBoard[SIDE]){
   for(int i = 0; i <SIDE; i++){
    bigBoard[i].winner = ' ';

    for(int j=0; j<INNER_SIZE; i++){
        for(int k=0; k<INNER_SIZE; k++){
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







