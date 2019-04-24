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
int Eval(int subboard[10]){
    int value = 0;
    if(
        //columns
        (subboard[1] == 0 && subboard[4] == 0 && subboard[7] == 0)||
        (subboard[2] == 0 && subboard[5] == 0 && subboard[8] == 0)||
        (subboard[3] == 0 && subboard[6] == 0 && subboard[9] == 0)||
        //rows
        (subboard[1] == 0 && subboard[2] == 0 && subboard[3] == 0)||
        (subboard[4] == 0 && subboard[5] == 0 && subboard[6] == 0)||
        (subboard[7] == 0 && subboard[8] == 0 && subboard[9] == 0)||
        //diagnoses
        (subboard[1] == 0 && subboard[5] == 0 && subboard[9] == 0)||
        (subboard[3] == 0 && subboard[5] == 0 && subboard[7] == 0)
    ){value = value + MAKING_3Xs;}
    else if(
        //columns
        (subboard[1] == 1 && subboard[4] == 1 && subboard[7] == 1)||
        (subboard[2] == 1 && subboard[5] == 1 && subboard[8] == 1)||
        (subboard[3] == 1 && subboard[6] == 1 && subboard[9] == 1)||
        //rows
        (subboard[1] == 1 && subboard[2] == 1 && subboard[3] == 1)||
        (subboard[4] == 1 && subboard[5] == 1 && subboard[6] == 1)||
        (subboard[7] == 1 && subboard[8] == 1 && subboard[9] == 1)||
        //diagnoses
        (subboard[1] == 1 && subboard[5] == 1 && subboard[9] == 1)||
        (subboard[3] == 1 && subboard[5] == 1 && subboard[7] == 1)
    ){value = value + MAKING_3Os;}
    // rows
    for(int i = 1; i<10;i = i+3){
        if(subboard[i] != 1 && subboard[i+1] != 1 && subboard[i+2] != 1){
            if(
                (subboard[i] ==0 && subboard[i+1] ==0 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==0)||
                (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==0)
            ){value = value + MAKING_2Xs;}
            if(
                (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==0)
            ){value = value + BASIC_SCORE;}
        }
    }
    //columns
    for(int i = 1; i<4;i++){
        if(subboard[i] != 1 && subboard[i+3] != 1 && subboard[i+6] != 1){
            if(
                (subboard[i] ==0 && subboard[i+3] ==0 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==0 && subboard[i+6] ==0)||
                (subboard[i] ==0 && subboard[i+3] ==2 && subboard[i+6] ==0)
            ){value = value + MAKING_2Xs;}
            if(
                (subboard[i] ==0 && subboard[i+3] ==2 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==0 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==0)
            ){value = value + BASIC_SCORE;}
        }
    }
    //diagnoses
   if(subboard[1] != 1 && subboard[5] != 1 && subboard[9] != 1){
        if(
            (subboard[1] ==0 && subboard[5] ==0 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==0 && subboard[9] ==0)||
            (subboard[1] ==0 && subboard[5] ==2 && subboard[9] ==0)
        ){value = value + MAKING_2Xs;}
        if(
            (subboard[1] ==0 && subboard[5] ==2 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==0 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==0)
        ){value = value + BASIC_SCORE;}
    }
    if(subboard[3] != 1 && subboard[5] != 1 && subboard[7] != 1){
        if(
            (subboard[3] ==0 && subboard[5] ==0 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==0)||
            (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==0)
        ){value = value + MAKING_2Xs;}
        if(
            (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==0)
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
int isFull(int board[10]){
    for(int i = 1;i<10;i++){
        if(board[i] == 2){
            return 0;
        }
    }
    return 1;
}
int *alphabeta(int board[10], int next_move, int depth, int alpha, int beta, int Player)
{
    int *val2 = (int*) malloc(2*sizeof(int));
    if(isFull(board)==1 || depth == 0){
        val2[0] = next_move;
        val2[1] = Eval(board);
        return val2;
    }
    if(!Player){
        for (int i = 1; i <10;i++){
            if(board[i] == 2){
                board[i] = 0;
                if(next_move <= 0){
                    next_move = i;
                }
                val2 = alphabeta(board,next_move,depth-1,alpha,beta,!Player);
                // update next_move when there is a better choice
                if(alpha < val2[1]){
                    next_move = i;
                }
                alpha = max(alpha,val2[1]);
                board[i] = 2;
                if (alpha >= beta){
                    return val2;
                }
            }
        }
        return val2;
    }
    else{
        for (int i = 1; i <10;i++){
            if(board[i] == 2){
                board[i] = 1;
                if(next_move <= 0){
                    next_move = i;
                }
                val2 = alphabeta(board,next_move,depth-1,alpha,beta,!Player);
                // update next_move when there is a better choice
                if(beta > val2[1]){
                    next_move = i;
                }
                beta = min(beta, val2[1]);
                board[i] = 2;
                if (alpha >= beta){
                    return val2;
                }
            }
        }
        return val2;
    }
}
// int main(){
//     int *val = (int*) malloc(2*sizeof(int));
//     int v;
//     int board[10][10] = {
//         {},
//         {' ',2,'e','e','e','e','e','e','e','e'},
//         {' ','e','e','e','e','e','e','e','e','e'},
//         {' ','e','e',0,'e','e','e','e','e','e'},
//         {' ','e','e','e','e','e','e','e','e','e'},
//         {' ','e','e','e','e','e','e','e','e','e'},
//         {' ','e',1,'e','O','e','X','X','e','e'},
//         {' ','e','e','e','e','e','e','e','e','e'},
//         {' ','e','e','e','e','e','e','e','e','e'},
//         {' ','e','e','e','e','e','e','e','e','e'}
//     };
//     val = alphabeta(board[6],-1,5,-2000,2000,1);
//     printf("(%d):%d\n",val[0],val[1]);
//     return 0;
// }


