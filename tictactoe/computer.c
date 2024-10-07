#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "const.h"
#include <stdbool.h>

bool is_empty(int move, char board[SIDE][SIDE])
{
    int row = (move-1)/SIDE;
    int column = (move-1)%SIDE;
    if(board[row][column]==' ')
    {
        return true;
    }
    else{
        return false;
    }
}

int finish(char board[SIDE][SIDE])
{
    //checking rows
    for(int i=0; i< SIDE; i++)
    {
        if(board[i][0]==COMPUTER_SYMBOL && board[i][1]== COMPUTER_SYMBOL && board[i][2] == ' '){
            return (i*SIDE+3);
        }
        if(board[i][0]==COMPUTER_SYMBOL && board[i][2]== COMPUTER_SYMBOL && board[i][1] == ' '){
            return (i*SIDE+2);
        }
        if(board[i][1]==COMPUTER_SYMBOL && board[i][2]== COMPUTER_SYMBOL && board[i][0] == ' '){
            return (i*SIDE+1);
        }
    }
    //checking columns
    for(int i=0; i<SIDE; i++)
    {
        if(board[0][i]==COMPUTER_SYMBOL && board[1][i]==COMPUTER_SYMBOL && board[2][i] == ' '){
            return (7+i); 
        }
    }
    for(int i=0; i<SIDE; i++){
        if(board[1][i]==COMPUTER_SYMBOL && board[2][i]==COMPUTER_SYMBOL && board[0][i] == ' '){
            return i;
        }
    }
    for(int i=0; i<SIDE; i++){
        if(board[0][i]==COMPUTER_SYMBOL && board[2][i]==COMPUTER_SYMBOL && board[1][i] == ' '){
            return (4+i);
        }
    }
    //checking diagonals
    if(board[0][0]==board[1][1] && board[0][0]==COMPUTER_SYMBOL && board[2][2]==' '){
        return 9;
    }
    else if(board[0][0]==' ' && board[1][1]==COMPUTER_SYMBOL && board[2][2]==board[1][1]){
        return 1;
    }
    else if((board[0][0]==board[2][2] && board[0][0]==COMPUTER_SYMBOL && board[1][1]==' ') || (board[0][2]==board[2][0] && board[0][2]==COMPUTER_SYMBOL && board[1][1]==' ')){
        return 5;
    }
    else if(board[0][2]==COMPUTER_SYMBOL && board[0][2]==board[1][1] && board[2][0]==' '){
        return 7;
    }
    if(board[0][2]==' ' && board[1][1]==COMPUTER_SYMBOL && board[0][2]==board[1][1]){
        return 3;
        }
    return 0;
}


int defence(char board[SIDE][SIDE]){
    //checking lines
    for(int i=0; i< SIDE; i++){
        if(board[i][0]==PLAYER1_SYMBOL && board[i][1]== PLAYER1_SYMBOL && board[i][2] == ' '){
            return (i*SIDE+3);
        }
        if(board[i][0]==PLAYER1_SYMBOL && board[i][2]== PLAYER1_SYMBOL && board[i][1] == ' '){
            return (i*SIDE+2);
        }
        if(board[i][1]==PLAYER1_SYMBOL && board[i][2]== PLAYER1_SYMBOL && board[i][0] == ' '){
            return (i*SIDE+1);
        }
    }
    //checking rows
    for(int i=0; i<SIDE; i++){
        if(board[0][i]==PLAYER1_SYMBOL && board[1][i]==PLAYER1_SYMBOL && board[2][i] == ' '){
            return (7+i);
        }
    }
    for(int i=0; i<SIDE; i++){
        if(board[1][i]==PLAYER1_SYMBOL && board[2][i]==PLAYER1_SYMBOL && board[0][i] == ' '){
            return i;
        }
    }
    for(int i=0; i<SIDE; i++){
        if(board[0][i]==PLAYER1_SYMBOL && board[2][i]==PLAYER1_SYMBOL && board[1][i] == ' '){
            return (4+i);
        }
    }
    //checking diagonals
    if(board[0][0]==board[1][1] && board[0][0]==PLAYER1_SYMBOL && board[2][2]==' '){
        return 9;
    }
    else if(board[0][0]==' ' && board[1][1]==PLAYER1_SYMBOL && board[2][2]==board[1][1]){
        return 1;
    }
    else if((board[0][0]==board[2][2] && board[0][0]==PLAYER1_SYMBOL && board[1][1]==' ') || (board[0][2]==board[2][0] && board[0][2]==PLAYER1_SYMBOL && board[1][1]==' ')){
        return 5;
    }
    else if(board[0][2]==PLAYER1_SYMBOL && board[0][2]==board[1][1] && board[2][0]==' '){
        return 7;
    }
    if(board[0][2]==' ' && board[1][1]==PLAYER1_SYMBOL && board[0][2]==board[1][1]){
        return 3;
        }
    return 0;
}

 int computer_move_simple(char board[SIDE][SIDE])
 {
    static int initialized = 0;
    if (!initialized) 
    {
        srand(time(NULL));  
        initialized = 1;     
    }
     while(1)
    {
        int move = (rand()%(SIDE*SIDE))+1;
        if(is_empty(move, board))
        {
            return move;
        }
    }
 }


int computer_move(char board[SIDE][SIDE])
{
    int move = 0;
    if(finish(board)!=0){
        move = finish(board);
    }
    else if(defence(board)!=0){
        move = defence(board);
    }
    else{
        move = computer_move_simple(board);
    }
    return move;

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