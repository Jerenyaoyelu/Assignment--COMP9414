#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define AL -20000000
#define BT 20000000
#ifndef max
    #define max(a,b)(((a)>(b))?(a):(b))
#endif
#ifndef min
    #define min(a,b)(((a)<(b))?(a):(b))
#endif

#include"BinomialHeapPQ.c"
/*
// Heuristic:
//version4:
possible wins of target(having 2 in a row/column/diagnose)
1. if there is a blocking of a 2 !target, counts 1
2. 1 target in a row/column/diagnose counts 0.2
*/
//Eval version 4
int Eval(int subboard[10],int target){
    int wins = 0;
    for(int i = 1; i<10;i = i+3){
        if(// having 2 targets
            (subboard[i] ==target && subboard[i+1] ==target && subboard[i+2] ==2)||
            (subboard[i] ==2 && subboard[i+1] ==target && subboard[i+2] ==target)||
            (subboard[i] ==target && subboard[i+1] ==2 && subboard[i+2] ==target)
        ){wins++;}
        if(// a blocking
            (subboard[i] ==!target && subboard[i+1] ==!target && subboard[i+2] ==target)||
            (subboard[i] ==target && subboard[i+1] ==!target && subboard[i+2] ==!target)||
            (subboard[i] ==!target && subboard[i+1] ==target && subboard[i+2] ==!target)
        ){wins++;}
        if(// having 1 target
            (subboard[i] ==target && subboard[i+1] ==2 && subboard[i+2] ==2)||
            (subboard[i] ==2 && subboard[i+1] ==target && subboard[i+2] ==2)||
            (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==target)
        ){wins = wins + 0.2;}
        // empty row
        if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
            wins = wins + 0.2;
        }
    }
    //columns
    for(int i = 1; i<4;i++){
        if(// having 2 targets
            (subboard[i] ==target && subboard[i+3] ==target && subboard[i+6] ==2)||
            (subboard[i] ==2 && subboard[i+3] ==target && subboard[i+6] ==target)||
            (subboard[i] ==target && subboard[i+3] ==2 && subboard[i+6] ==target)
        ){wins++;}
        if(// a blocking
            (subboard[i] ==!target && subboard[i+3] ==!target && subboard[i+6] ==target)||
            (subboard[i] ==target && subboard[i+3] ==!target && subboard[i+6] ==!target)||
            (subboard[i] ==!target && subboard[i+3] ==target && subboard[i+6] ==!target)
        ){wins++;}
        if(// having 1 target
            (subboard[i] ==target && subboard[i+3] ==2 && subboard[i+6] ==2)||
            (subboard[i] ==2 && subboard[i+3] ==target && subboard[i+6] ==2)||
            (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==target)
        ){wins = wins + 0.2;}
        // empty row
        if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
            wins = wins + 0.2;
        }
    }
    //diagnoses
    if(// having 2 targets
        (subboard[1] ==target && subboard[5] ==target && subboard[9] ==2)||
        (subboard[1] ==2 && subboard[5] ==target && subboard[9] ==target)||
        (subboard[1] ==target && subboard[5] ==2 && subboard[9] ==target)
    ){wins++;}
    if(// a blocking
        (subboard[1] ==!target && subboard[5] ==!target && subboard[9] ==target)||
        (subboard[1] ==target && subboard[5] ==!target && subboard[9] ==!target)||
        (subboard[1] ==!target && subboard[5] ==target && subboard[9] ==!target)
    ){wins++;}
    if(//having 1 target
        (subboard[1] ==target && subboard[5] ==2 && subboard[9] ==2)||
        (subboard[1] ==2 && subboard[5] ==target && subboard[9] ==2)||
        (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==target)
    ){wins = wins + 0.2;}
    if(// having 2 targets
        (subboard[3] ==target && subboard[5] ==target && subboard[7] ==2)||
        (subboard[3] ==2 && subboard[5] ==target && subboard[7] ==target)||
        (subboard[3] ==target && subboard[5] ==2 && subboard[7] ==target)
    ){wins++;}
    if(// a blocking
        (subboard[3] ==!target && subboard[5] ==!target && subboard[7] ==target)||
        (subboard[3] ==target && subboard[5] ==!target && subboard[7] ==!target)||
        (subboard[3] ==!target && subboard[5] ==target && subboard[7] ==!target)
    ){wins++;}
    if(// having 1 target
        (subboard[3] ==target && subboard[5] ==2 && subboard[7] ==2)||
        (subboard[3] ==2 && subboard[5] ==target && subboard[7] ==2)||
        (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==target)
    ){wins = wins + 0.2;}
    return wins*10;
}
// check if can block the target player, yes return 1, otherwise return 0;
int Blocking(int subboard[10],int target, int position){
    //diagnoses
    if(
        (subboard[1] ==target && subboard[5] ==target && subboard[9] ==2)&&
        position == 9
    ){return 1;}
    if(
        (subboard[1] ==2 && subboard[5] ==target && subboard[9] ==target)&&
        position == 1
    ){return 1;}
    if(
        (subboard[1] ==target && subboard[5] ==2 && subboard[9] ==target)&&
        position == 5
    ){return 1;}
    if(
        (subboard[3] ==target && subboard[5] ==target && subboard[7] ==2)&&
        position == 7
    ){return 1;}
    if(
        (subboard[3] ==2 && subboard[5] ==target && subboard[7] ==target)&&
        position == 3
    ){return 1;}
    if(
        (subboard[3] ==target && subboard[5] ==2 && subboard[7] ==target)&&
        position == 5
    ){return 1;}
    //rows
    for(int i = 1; i<10;i = i+3){
        if(
            (subboard[i] ==target && subboard[i+1] ==target && subboard[i+2] ==2) && 
            position == i+2
        ){return 1;}
        if(
            (subboard[i] ==2 && subboard[i+1] ==target && subboard[i+2] ==target) &&
            position == i
        ){return 1;}
        if(
            (subboard[i] ==target && subboard[i+1] ==2 && subboard[i+2] ==target)&&
            position == i+1
        ){return 1;}
    }
    //columns
    for(int i = 1; i<4;i++){
        if(
            (subboard[i] ==target && subboard[i+3] ==target && subboard[i+6] ==2)&&
            position == i+6
        ){return 1;}
        if(
            (subboard[i] ==2 && subboard[i+3] ==target && subboard[i+6] ==target)&&
            position == i
        ){return 1;}
        if(
            (subboard[i] ==target && subboard[i+3] ==2 && subboard[i+6] ==target)&&
            position == i+3
        ){return 1;}
    }
    return 0;
}
// calculate the number of target player in a sub-board
int Cal(int subboard[10],int target){
    int count = 0;
    for(int i = 1;i<10;i++){
        if(target == subboard[i]){
            count++;
        }
    }
    return count;
}
// can check if next board has 3 targets or 2 targets and 1 empty
// mode can only be 2/3
int isWon(int subboard[10],int target, int mode){
    if(mode == 3){//having 3 targets
        if(
            //columns
            (subboard[1] == target && subboard[4] == target && subboard[7] == target)||
            (subboard[2] == target && subboard[5] == target && subboard[8] == target)||
            (subboard[3] == target && subboard[6] == target && subboard[9] == target)||
            //rows
            (subboard[1] == target && subboard[2] == target && subboard[3] == target)||
            (subboard[4] == target && subboard[5] == target && subboard[6] == target)||
            (subboard[7] == target && subboard[8] == target && subboard[9] == target)||
            //diagnoses
            (subboard[1] == target && subboard[5] == target && subboard[9] == target)||
            (subboard[3] == target && subboard[5] == target && subboard[7] == target)
        ){return 1;}
    }else{//having 2 targets
        //rows
        for(int i = 1; i<10;i = i+3){
            if(
                (subboard[i] ==target && subboard[i+1] ==target && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==target && subboard[i+2] ==target)||
                (subboard[i] ==target && subboard[i+1] ==2 && subboard[i+2] ==target)
            ){return 1;}
        }
        //columns
        for(int i = 1; i<4;i++){
            if(
                (subboard[i] ==target && subboard[i+3] ==target && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==target && subboard[i+6] ==target)||
                (subboard[i] ==target && subboard[i+3] ==2 && subboard[i+6] ==target)
            ){return 1;}
        }
        //diagnoses
        if(
            (subboard[1] ==target && subboard[5] ==target && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==target && subboard[9] ==target)||
            (subboard[1] ==target && subboard[5] ==2 && subboard[9] ==target)
        ){return 1;}
        if(
            (subboard[3] ==target && subboard[5] ==target && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==target && subboard[7] ==target)||
            (subboard[3] ==target && subboard[5] ==2 && subboard[7] ==target)
        ){return 1;}
    }
    return 0;
}
/*
//alpha beta search Algorithm pseudo code:
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

//check a sub-board is full
int isFull(int board[10]){
    for(int i = 1;i<10;i++){
        if(board[i] == 2){
            return 0;
        }
    }
    return 1;
}
// get the score for each potential case
int alphabeta(int board[10][10], int prev_move, int depth, int alpha, int beta, int Player)
{
    // int val;
    if(isFull(board[prev_move])==1 || depth == 0){
        return Eval(board[prev_move],!Player);
    }else
    {   
        for (int i = 1; i <10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = Player;
                if(Player == 0){
                    // place where I adjusted
                    // go to the next board
                    alpha = max(alpha,alphabeta(board,i,depth-1,alpha,beta,!Player));
                    board[prev_move][i] = 2;
                    if(alpha >= beta){return alpha;}
                }else{
                    // place where I adjusted
                    // go to the next board
                    beta = min(beta, alphabeta(board,i,depth-1,alpha,beta,!Player));
                    board[prev_move][i] = 2;
                    if(alpha >= beta){return beta;}
                }
            }
        }
        if(Player == 0){
            return alpha;
        }else{
            return beta;
        }        
    }
}
// get the best move
int getBestMove(int board[10][10], int prev_move, int depth, int player){
    int val;
    int Performance[10] = {0,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    BinomialHeap * PQ1 = newHeap();
    if(Cal(board[prev_move],2) == 9 && Cal(board[5],player) == 0&& Cal(board[5],!player) == 0){
        return 5;
    }
    // get performance of each potential move
    for(int i = 1; i< 10;i++){
        if(board[prev_move][i] == 2){
            board[prev_move][i] = player;
            val = alphabeta(board,i,depth,AL,BT,!player);
            board[prev_move][i] = 2;
            Insert(PQ1,val,i,0,0,0);
        }
    }
    // sort the moves in increasing order
    for(int i = 1; i <10;i++){
        if(PQ1->smallestB == NULL){break;}
        Performance[i] = RemoveMin(PQ1)->TaskName;
        Performance[0] ++;
        // check if win at this step by using blocking function trickly.
        // if win, choose first.
        if(Blocking(board[prev_move],player,Performance[i]) == 1){
            return Performance[i];
        }
    }

    if(Performance[0]==1){
        return Performance[1];
    }else{
        if(player == 0){
            //reversed visiting the array
            for(int j= Performance[0]; j>0 ;j--){
                // if this move bolcks, and dont lose in next board, then choose it
                if(Blocking(board[prev_move],!player,Performance[j]) == 1 && isWon(board[Performance[j]],!player,2) != 1){
                    return Performance[j];
                }else{
                    //if the opponent dont have 2 objects in a row/column/diagonse, then it is good to go.
                    board[prev_move][Performance[j]] = player;
                    if(isWon(board[Performance[j]],!player,2)!=1){
                        board[prev_move][Performance[j]] = 2;
                        return Performance[j];
                    }
                    board[prev_move][Performance[j]] = 2;
                }
            }
        }else{
            for(int j=1; j<= Performance[0]; j++){
                // if this move bolcks, and dont lose in next board, then choose it
                if(Blocking(board[prev_move],!player,Performance[j]) == 1 && isWon(board[Performance[j]],!player,2) != 1){
                    return Performance[j];
                }else{
                    //if the opponent dont have 2 objects in a row/column/diagonse, then it is good to go.
                    board[prev_move][Performance[j]] = player;
                    if(isWon(board[Performance[j]],!player,2)!=1){
                        board[prev_move][Performance[j]] = 2;
                        return Performance[j];
                    }
                    board[prev_move][Performance[j]] = 2;
                }
            }
        }
        return Performance[Performance[0]];
    }
}


