#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define H2Os -2
#define H3Xs 10
#define H2Xs 1
#define BASIC_SCORE 0
#define H3Os -10
#define AL -20000000
#define BT 20000000
#ifndef max
    #define max(a,b)(((a)>(b))?(a):(b))
#endif
#ifndef min
    #define min(a,b)(((a)<(b))?(a):(b))
#endif
/*
// Heuristic:
//version2:
1.had 3X(i):10
2.had 2X(i): 1
3.had 3O(i): -20
4.had 2O(i): -2
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
    ){
        value = value + H3Xs;
        return value;
    }
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
    ){
        value = value + H3Os;
        return value;
    }
    // rows
    for(int i = 1; i<10;i = i+3){
        if(subboard[i] != 1 && subboard[i+1] != 1 && subboard[i+2] != 1){
            if(
                (subboard[i] ==0 && subboard[i+1] ==0 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==0)||
                (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==0)
            ){value = value + H2Xs;}
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
            ){value = value + H2Xs;}
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
        ){value = value + H2Xs;}
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
        ){value = value + H2Xs;}
        if(
            (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==0)
        ){value = value + BASIC_SCORE;}
    }

    // Making 2 Os
    // rows
    for(int i = 1; i<10;i = i+3){
        if(subboard[i] != 1 && subboard[i+1] != 1 && subboard[i+2] != 1){
            if(
                (subboard[i] ==1 && subboard[i+1] ==1 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==1 && subboard[i+2] ==1)||
                (subboard[i] ==1 && subboard[i+1] ==2 && subboard[i+2] ==1)
            ){value = value + H2Os;}
        }
    }
    //columns
    for(int i = 1; i<4;i++){
        if(subboard[i] != 1 && subboard[i+3] != 1 && subboard[i+6] != 1){
            if(
                (subboard[i] ==1 && subboard[i+3] ==1 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==1 && subboard[i+6] ==1)||
                (subboard[i] ==1 && subboard[i+3] ==2 && subboard[i+6] ==1)
            ){value = value + H2Os;}
        }
    }
    //diagnoses
   if(subboard[1] != 1 && subboard[5] != 1 && subboard[9] != 1){
        if(
            (subboard[1] ==1 && subboard[5] ==1 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==1 && subboard[9] ==1)||
            (subboard[1] ==1 && subboard[5] ==2 && subboard[9] ==1)
        ){value = value + H2Os;}
    }
    if(subboard[3] != 1 && subboard[5] != 1 && subboard[7] != 1){
        if(
            (subboard[3] ==1 && subboard[5] ==1 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==1 && subboard[7] ==1)||
            (subboard[3] ==1 && subboard[5] ==2 && subboard[7] ==1)
        ){value = value + H2Os;}
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
int alphabeta(int board[10][10], int prev_move, int depth, int alpha, int beta, int Player)
{
    // int val;
    if(isFull(board[prev_move])==1 || depth == 0){
        return Eval(board[prev_move]);
    }
    if(Player == 0){
        for (int i = 1; i <10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = 0;
                alpha = max(alpha,alphabeta(board,i,depth-1,alpha,beta,!Player));
                board[prev_move][i] = 2;
                if (alpha >= beta){
                    return alpha;
                }
            }
        }
        return alpha;
    }
    else{
        for (int i = 1; i <10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = 1;
                beta = min(beta, alphabeta(board,i,depth-1,alpha,beta,!Player));
                board[prev_move][i] = 2;
                if (alpha >= beta){
                    return beta;
                }
            }
        }
        return beta;
    }
}
int getBestMove(int board[10][10], int prev_move, int depth, int player){
    int val;
    int BM = 0;
    // int X_array[10];
    // int O_array[10];
    // int BS = -1000;
    if(player == 0){
        int BS = -1000;
        for(int i = 1; i< 10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = 0;
                val = alphabeta(board,i,depth,AL,BT,1);
                board[prev_move][i] = 2;
                // X_array[i] = val;
                if(val > BS){
                    BS = val;
                    BM = i;
                }
                printf("%d\n",val);
            }
        }
    }else
    {
        int BS = 1000;
        for(int i = 1; i< 10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = 1;
                val = alphabeta(board,i,depth,AL,BT,0);
                board[prev_move][i] = 2;
                // X_array[i] = val;
                if(val < BS){
                    BS = val;
                    BM = i;
                }
                printf("%d\n",val);
            }
        }
    }
    
    // //watch on next move
    // for(int i = 1; i <10; i ++){
    //     if(board[prev_move][i] == 2){
    //         if(X_array[i] != 0){
    //             board[prev_move][i] = 0;
    //             //if next move is that I win, then choose first.
    //             if(Eval(board[prev_move])==10){
    //                 board[prev_move][i] = 2;
    //                 return i;
    //             }else{
    //                 // choose the worst next next move for the opponent
    //                 int worst_oppent = -10000;
    //                 for(int j = 1; j<10;j++){
    //                     if(board[i][j] == 2){
    //                         board[i][j] = 1;
    //                         worst_oppent = max(worst_oppent, Eval(board[i]));
    //                         board[i][j] = 2;
    //                     }
    //                 }
    //                 board[prev_move][i] = 2;
    //                 if(BS > X_array[i] - worst_oppent){
    //                     BS = X_array[i] - worst_oppent;
    //                     BM = i;
    //                 }
    //             }
    //         }
    //     }
    // }
    return BM;
}


