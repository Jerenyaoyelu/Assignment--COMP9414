#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BLOCK 1000
#define MAKING_3Xs 10000
#define MAKING_2Xs 2
#define BASIC_SCORE 1
#define MAKING_3Os -5000
#ifndef max
    #define max(a,b)(((a)>(b))?(a):(b))
#endif
#ifndef min
    #define min(a,b)(((a)<(b))?(a):(b))
#endif
/*
// Heuristic:
//version2:
1.had 3X(i):10000
2.had 2X(i): 10
3.n of rows/columns/diagonses having X(i): n
4.had 3O(i): -5000
// 5.Blockling 3O(i): 1000
*/
//Eval version 2
int Eval(char subboard[10]){
    int value = 0;
    if(
        //columns
        (subboard[1] == 'X' && subboard[4] == 'X' && subboard[7] == 'X')||
        (subboard[2] == 'X' && subboard[5] == 'X' && subboard[8] == 'X')||
        (subboard[3] == 'X' && subboard[6] == 'X' && subboard[9] == 'X')||
        //rows
        (subboard[1] == 'X' && subboard[2] == 'X' && subboard[3] == 'X')||
        (subboard[4] == 'X' && subboard[5] == 'X' && subboard[6] == 'X')||
        (subboard[7] == 'X' && subboard[8] == 'X' && subboard[9] == 'X')||
        //diagnoses
        (subboard[1] == 'X' && subboard[5] == 'X' && subboard[9] == 'X')||
        (subboard[3] == 'X' && subboard[5] == 'X' && subboard[7] == 'X')
    ){value = value + MAKING_3Xs;}
    else if(
        //columns
        (subboard[1] == 'O' && subboard[4] == 'O' && subboard[7] == 'O')||
        (subboard[2] == 'O' && subboard[5] == 'O' && subboard[8] == 'O')||
        (subboard[3] == 'O' && subboard[6] == 'O' && subboard[9] == 'O')||
        //rows
        (subboard[1] == 'O' && subboard[2] == 'O' && subboard[3] == 'O')||
        (subboard[4] == 'O' && subboard[5] == 'O' && subboard[6] == 'O')||
        (subboard[7] == 'O' && subboard[8] == 'O' && subboard[9] == 'O')||
        //diagnoses
        (subboard[1] == 'O' && subboard[5] == 'O' && subboard[9] == 'O')||
        (subboard[3] == 'O' && subboard[5] == 'O' && subboard[7] == 'O')
    ){value = value + MAKING_3Os;}
    // rows
    for(int i = 1; i<10;i = i+3){
        if(subboard[i] != 'O' && subboard[i+1] != 'O' && subboard[i+2] != 'O'){
            if(
                (subboard[i] =='X' && subboard[i+1] =='X' && subboard[i+2] =='e')||
                (subboard[i] =='e' && subboard[i+1] =='X' && subboard[i+2] =='X')||
                (subboard[i] =='X' && subboard[i+1] =='e' && subboard[i+2] =='X')
            ){value = value + MAKING_2Xs;}
            if(
                (subboard[i] =='X' && subboard[i+1] =='e' && subboard[i+2] =='e')||
                (subboard[i] =='e' && subboard[i+1] =='X' && subboard[i+2] =='e')||
                (subboard[i] =='e' && subboard[i+1] =='e' && subboard[i+2] =='X')
            ){value = value + BASIC_SCORE;}
        }
    }
    //columns
    for(int i = 1; i<4;i++){
        if(subboard[i] != 'O' && subboard[i+3] != 'O' && subboard[i+6] != 'O'){
            if(
                (subboard[i] =='X' && subboard[i+3] =='X' && subboard[i+6] =='e')||
                (subboard[i] =='e' && subboard[i+3] =='X' && subboard[i+6] =='X')||
                (subboard[i] =='X' && subboard[i+3] =='e' && subboard[i+6] =='X')
            ){value = value + MAKING_2Xs;}
            if(
                (subboard[i] =='X' && subboard[i+3] =='e' && subboard[i+6] =='e')||
                (subboard[i] =='e' && subboard[i+3] =='X' && subboard[i+6] =='e')||
                (subboard[i] =='e' && subboard[i+3] =='e' && subboard[i+6] =='X')
            ){value = value + BASIC_SCORE;}
        }
    }
    //diagnoses
   if(subboard[1] != 'O' && subboard[5] != 'O' && subboard[9] != 'O'){
        if(
            (subboard[1] =='X' && subboard[5] =='X' && subboard[9] =='e')||
            (subboard[1] =='e' && subboard[5] =='X' && subboard[9] =='X')||
            (subboard[1] =='X' && subboard[5] =='e' && subboard[9] =='X')
        ){value = value + MAKING_2Xs;}
        if(
            (subboard[1] =='X' && subboard[5] =='e' && subboard[9] =='e')||
            (subboard[1] =='e' && subboard[5] =='X' && subboard[9] =='e')||
            (subboard[1] =='e' && subboard[5] =='e' && subboard[9] =='X')
        ){value = value + BASIC_SCORE;}
    }
    if(subboard[3] != 'O' && subboard[5] != 'O' && subboard[7] != 'O'){
        if(
            (subboard[3] =='X' && subboard[5] =='X' && subboard[7] =='e')||
            (subboard[3] =='e' && subboard[5] =='X' && subboard[7] =='X')||
            (subboard[3] =='X' && subboard[5] =='e' && subboard[7] =='X')
        ){value = value + MAKING_2Xs;}
        if(
            (subboard[3] =='X' && subboard[5] =='e' && subboard[7] =='e')||
            (subboard[3] =='e' && subboard[5] =='X' && subboard[7] =='e')||
            (subboard[3] =='e' && subboard[5] =='e' && subboard[7] =='X')
        ){value = value + BASIC_SCORE;}
    }
    return value;
}

/*
//alpha beta search Algorithm:
function alphabeta( node, depth, α, β )
    if node is a terminal node or depth == 0
        return heuristic value of node
    if we are to play at node
        foreach child of node
            let α = max( α, alphabeta( child, depth-1, α, β ))
            if α ≥ β
                return α
        return α
    else // opponent is to play at node
        foreach child of node
            let β = min( β, alphabeta( child, depth-1, α, β ))
            if β ≤ α
                return β
        return β
*/
int isFull(char board[10]){
    int  t = 0;
    for(int i = 1;i<10;i++){
        if(board[i] == 'e'){
            return 0;
        }
    }
    return 1;
}
int *alphabeta(char board[10], int next_move, int depth, int alpha, int beta, int Player)
{
    int *val2 = (int*) malloc(2*sizeof(int));
    int val;
    if(isFull(board)==1 || depth == 0){
        val2[0] = next_move;
        val2[1] = Eval(board);
        return val2;
    }
    if(Player){
        for (int i = 1; i <10;i++){
            if(board[i] == 'e'){
                board[i] = 'X';
                if(next_move <= 0){
                    next_move = i;
                }
                val2 = alphabeta(board,next_move,depth-1,alpha,beta,!Player);
                // update next_move when there is a better choice
                if(alpha < val2[1]){
                    next_move = i;
                }
                alpha = max(alpha,val2[1]);
                board[i] = 'e';
                if (alpha >= beta){
                    return val2;
                }
            }
        }
        return val2;
    }
    else{
        for (int i = 1; i <10;i++){
            if(board[i] == 'e'){
                board[i] = 'O';
                if(next_move <= 0){
                    next_move = i;
                }
                val2 = alphabeta(board,next_move,depth-1,alpha,beta,!Player);
                // update next_move when there is a better choice
                if(beta > val2[1]){
                    next_move = i;
                }
                beta = min(beta, val2[1]);
                board[i] = 'e';
                if (alpha >= beta){
                    return val2;
                }
            }
        }
        return val2;
    }
}
int main(){
    int *val = (int*) malloc(2*sizeof(int));
    int v;
    char board[10][10] = {
        {},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','X','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','O','e','O','e','X','X','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'}
    };
    val = alphabeta(board[6],-1,5,-2000,2000,1);
    printf("(%d):%d\n",val[0],val[1]);
    return 0;
}


