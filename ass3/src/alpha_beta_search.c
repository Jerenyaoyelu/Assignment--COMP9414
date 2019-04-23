#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BLOCK 1000
#define MAKING_3Xs 10000
#define MAKING_2Xs 2
#define BASIC_SCORE 1
#ifndef max
    #define max(a,b)(((a)>(b))?(a):(b))
#endif
#ifndef min
    #define min(a,b)(((a)<(b))?(a):(b))
#endif
/*
// Heuristic:
1.having 3X(i):10000
2.having 2X(i): 10
3.n of rows/columns/diagonses having X(i): n
// 4.i+1 board has already had 2O(i+1): -2000
5.Blockling 3O(i): 1000



Priority1:
    maximize( # of boards having 2X(i) - # of boards having 2O(i))
Priority2:
    next board being empty comes first
Priority3:
    maximize( (# of X(i) - # of O(i)) - (# of O(i+1) - # of X(i+1)))
*/
int Eval(char subboard[10], int this_move){
    int value = 0;
    switch (this_move)
    {
        case 1:
            if(//making 3 Xs
                (subboard[4] == 'X' && subboard[7] == 'X')||
                (subboard[2] == 'X' && subboard[3] == 'X')||
                (subboard[5] == 'X' && subboard[9] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[4] == 'O' && subboard[7] == 'O')||
                (subboard[2] == 'O' && subboard[3] == 'O')||
                (subboard[5] == 'O' && subboard[9] == 'O')
            ){value = value + BLOCK;}
            if(// columns having X(i)
                subboard[4] != 'O' && subboard[7] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[4] == 'X' || subboard[7] == 'X'){
                    value = value +MAKING_2Xs;
                }
            }
            if(// rows having X(i)
                subboard[2] != 'O' && subboard[3] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[2] == 'X' || subboard[3] == 'X'){
                    value = value +MAKING_2Xs;
                }
            }
            if(// diagonses having X(i)
                subboard[5] != 'O' && subboard[9] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[5] == 'X' || subboard[9] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 2:
            if(//making 3 Xs
                (subboard[1] == 'X' && subboard[3] == 'X')||
                (subboard[5] == 'X' && subboard[8] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[1] == 'O' && subboard[3] == 'O')||
                (subboard[5] == 'O' && subboard[8] == 'O')
            ){value = value + BLOCK;}
            if(// rows having X(i)
                subboard[1] != 'O' && subboard[3] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[1] == 'X' || subboard[3] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// columns having X(i)
                subboard[5] != 'O' && subboard[8] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[5] == 'X' || subboard[8] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 3:
            if(//making 3 Xs
                (subboard[1] == 'X' && subboard[2] == 'X')||
                (subboard[5] == 'X' && subboard[7] == 'X')||
                (subboard[6] == 'X' && subboard[9] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[1] == 'O' && subboard[2] == 'O')||
                (subboard[5] == 'O' && subboard[7] == 'O')||
                (subboard[6] == 'O' && subboard[9] == 'O')
            ){value = value + BLOCK;}
            if(// rows having X(i)
                subboard[1] != 'O' && subboard[2] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[1] == 'X' || subboard[2] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// diagnoses having X(i)
                subboard[5] != 'O' && subboard[7] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[5] == 'X' || subboard[7] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// colunms having X(i)
                subboard[6] != 'O' && subboard[9] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[6] == 'X' || subboard[9] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 4:
            if(//making 3 Xs
                (subboard[1] == 'X' && subboard[7] == 'X')||
                (subboard[5] == 'X' && subboard[6] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[1] == 'O' && subboard[7] == 'O')||
                (subboard[5] == 'O' && subboard[6] == 'O')
            ){value = value + BLOCK;}
            if(// columns having X(i)
                subboard[1] != 'O' && subboard[7] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[1] == 'X' || subboard[7] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// rows having X(i)
                subboard[5] != 'O' && subboard[6] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[5] == 'X' || subboard[6] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 5:
            if(//making 3 Xs
                (subboard[1] == 'X' && subboard[9] == 'X')||
                (subboard[3] == 'X' && subboard[7] == 'X')||
                (subboard[2] == 'X' && subboard[8] == 'X')||
                (subboard[4] == 'X' && subboard[6] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[1] == 'O' && subboard[9] == 'O')||
                (subboard[3] == 'O' && subboard[7] == 'O')||
                (subboard[2] == 'O' && subboard[8] == 'O')||
                (subboard[4] == 'O' && subboard[6] == 'O')
            ){value = value + BLOCK;}
            if(// diagnoses having X(i)
                subboard[1] != 'O' && subboard[9] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[1] == 'X' || subboard[9] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// diagnoses having X(i)
                subboard[3] != 'O' && subboard[7] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[3] == 'X' || subboard[7] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// columns having X(i)
                subboard[2] != 'O' && subboard[8] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[2] == 'X' || subboard[8] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// rows having X(i)
                (subboard[4] != 'O' && subboard[6] != 'O')
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[4] == 'X' || subboard[6] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 6:
            if(//making 3 Xs
                (subboard[3] == 'X' && subboard[9] == 'X')||
                (subboard[4] == 'X' && subboard[5] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[3] == 'O' && subboard[9] == 'O')||
                (subboard[4] == 'O' && subboard[5] == 'O')
            ){value = value + BLOCK;}
            if(// columns having X(i)
                subboard[3] != 'O' && subboard[9] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[3] == 'X' || subboard[9] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// rows having X(i)
                subboard[4] != 'O' && subboard[5] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[4] == 'X' || subboard[5] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 7:
            if(//making 3 Xs
                (subboard[1] == 'X' && subboard[4] == 'X')||
                (subboard[8] == 'X' && subboard[9] == 'X')||
                (subboard[5] == 'X' && subboard[3] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[1] == 'O' && subboard[4] == 'O')||
                (subboard[8] == 'O' && subboard[9] == 'O')||
                (subboard[5] == 'O' && subboard[3] == 'O')
            ){value = value + BLOCK;}
            if(// columns having X(i)
                subboard[1] != 'O' && subboard[4] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[1] == 'X' || subboard[4] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// rows having X(i)
                subboard[8] != 'O' && subboard[9] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[8] == 'X' || subboard[9] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// diagonses having X(i)
                subboard[5] != 'O' && subboard[3] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[5] == 'X' || subboard[3] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 8:
            if(//making 3 Xs
                (subboard[7] == 'X' && subboard[9] == 'X')||
                (subboard[2] == 'X' && subboard[5] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[7] == 'O' && subboard[9] == 'O')||
                (subboard[2] == 'O' && subboard[5] == 'O')
            ){value = value + BLOCK;}
            if(// rows having X(i)
                subboard[7] != 'O' && subboard[9] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[7] == 'X' || subboard[9] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// columns having X(i)
                subboard[2] != 'O' && subboard[5] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[2] == 'X' || subboard[5] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        case 9:
            if(//making 3 Xs
                (subboard[7] == 'X' && subboard[8] == 'X')||
                (subboard[1] == 'X' && subboard[5] == 'X')||
                (subboard[3] == 'X' && subboard[6] == 'X')
            ){value = value + MAKING_3Xs;}
            else if(//blocking 3 Os
                (subboard[7] == 'O' && subboard[8] == 'O')||
                (subboard[1] == 'O' && subboard[5] == 'O')||
                (subboard[3] == 'O' && subboard[6] == 'O')
            ){value = value + BLOCK;}
            if(// rows having X(i)
                subboard[7] != 'O' && subboard[8] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[7] == 'X' || subboard[8] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// diagnoses having X(i)
                subboard[1] != 'O' && subboard[5] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[1] == 'X' || subboard[5] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            if(// colunms having X(i)
                subboard[3] != 'O' && subboard[6] != 'O'
            ){
                value = value + BASIC_SCORE;
                //makeing 2 Xs
                if(subboard[3] == 'X' || subboard[6] == 'X'){
                    value = value + MAKING_2Xs;
                }
            }
            break;
        default:
            break;
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
int *alphabeta(char board[10][10],int this_move, int prev_move, int depth, int alpha, int beta, int Player)
{
    if(Player){
        board[prev_move][this_move] = 'X';
    }else
    {
        board[prev_move][this_move] = 'O';
    }
    int *val = (int*) malloc(2*sizeof(int));
    if(isFull(board[prev_move])==1 || depth == 0){
        if(val[0] == 0){
            val[0] = this_move;
        }
        val[1] = Eval(board[prev_move],this_move);
    }
    if(Player == 1){
        for (int i = 1; i <10;i++){
            val = alphabeta(board,i,this_move,depth-1,val[1],beta,!Player);
            alpha = max(alpha, val[1]);
            if (alpha >= beta){
                if(val[0] == 0){
                    val[0] = i;
                }
                return val;
            }
        }
        if(val[0] == 0){
            val[0] = 9;
        }
        return val;
    }
    else{
        for (int i = 1; i <10;i++){
            val = alphabeta(board,i,this_move,depth-1,alpha,val[1],!Player);
            beta = min(beta, val[1]);
            if (alpha >= beta){
                if(val[0] == 0){
                    val[0] = i;
                }
                return val;
            }
        }
        if(val[0] == 0){
            val[0] = 9;
        }
        return val;
    }
}
int main(){
    int *val = (int*) malloc(2*sizeof(int));
    char board[10][10] = {
        {},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','X','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','O','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'},
        {' ','e','e','e','e','e','e','e','e','e'}
    };
    // for(int i = 1; i<10;i++){
    //     if(board[i][]=='e'){
    val = alphabeta(board,5,3,1,-2000,2000,0);
    printf("(%d):%d\n",val[0],val[1]);
        // }
    // }
    return 0;
}


