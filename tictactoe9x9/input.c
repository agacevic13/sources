#include <stdio.h>
#include "constants.h"

void initialization(struct smallBoard bigBoard[SIDE]){
    TRACE;
    for(int i = 0; i < SIDE; i++){
        TRACE;
        bigBoard[i].winner = ' ';

        for(int j=0; j < INNER_SIZE; j++){
            TRACE;
            for(int k=0; k<INNER_SIZE; k++){
                TRACE;
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
