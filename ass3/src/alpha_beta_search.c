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
/*
// Heuristic:
//version2:
1.had 3X(i):10
2.had 2X(i): 1
3.had 3O(i): -20
4.had 2O(i): -2

//version3:
possible wins: X/O *100
100 means X wins
0 means O wins
*/
//Eval version 3
int Eval(int subboard[10]){
    int X_wins = 0;
    int O_wins = 0;
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
    ){return 100;}
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
    ){return 0;}
    else{
        // rows
        for(int i = 1; i<10;i = i+3){
            if(// having 2 Xs
                (subboard[i] ==0 && subboard[i+1] ==0 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==0)||
                (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==0)
            ){X_wins++;}
            if(// having 1 X
                (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==0)
            ){X_wins++;}
            if(// having 2 Os
                (subboard[i] ==1 && subboard[i+1] ==1 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==1 && subboard[i+2] ==1)||
                (subboard[i] ==1 && subboard[i+1] ==2 && subboard[i+2] ==1)
            ){X_wins++;}
            if(// having 1 O
                (subboard[i] ==1 && subboard[i+1] ==2 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==1 && subboard[i+2] ==2)||
                (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==1)
            ){X_wins++;}
            // empty row
            if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
                X_wins++;
                O_wins++;
            }
        }
        //columns
        for(int i = 1; i<4;i++){
            if(// having 2 Xs
                (subboard[i] ==0 && subboard[i+3] ==0 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==0 && subboard[i+6] ==0)||
                (subboard[i] ==0 && subboard[i+3] ==2 && subboard[i+6] ==0)
            ){X_wins++;}
            if(// having 1 X
                (subboard[i] ==0 && subboard[i+3] ==2 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==0 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==0)
            ){X_wins++;}
            if(// having 2 Os
                (subboard[i] ==1 && subboard[i+3] ==1 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==1 && subboard[i+6] ==1)||
                (subboard[i] ==1 && subboard[i+3] ==2 && subboard[i+6] ==1)
            ){X_wins++;}
            if(// having 1 O
                (subboard[i] ==1 && subboard[i+3] ==2 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==1 && subboard[i+6] ==2)||
                (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==1)
            ){X_wins++;}
            // empty row
            if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
                X_wins++;
                O_wins++;
            }
        }
        //diagnoses
        if(// having 2 Xs
            (subboard[1] ==0 && subboard[5] ==0 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==0 && subboard[9] ==0)||
            (subboard[1] ==0 && subboard[5] ==2 && subboard[9] ==0)
        ){X_wins++;}
        if(//having 1 X
            (subboard[1] ==0 && subboard[5] ==2 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==0 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==0)
        ){X_wins++;}
        if(// having 2 Xs
            (subboard[3] ==0 && subboard[5] ==0 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==0)||
            (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==0)
        ){X_wins++;}
        if(// having 1 X
            (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==0)
        ){X_wins++;}
        if(// having 2 Os
            (subboard[1] ==1 && subboard[5] ==1 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==1 && subboard[9] ==1)||
            (subboard[1] ==1 && subboard[5] ==2 && subboard[9] ==1)
        ){O_wins++;}
        if(//having 1 O
            (subboard[1] ==1 && subboard[5] ==2 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==1 && subboard[9] ==2)||
            (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==1)
        ){O_wins++;}
        if(// having 2 Os
            (subboard[3] ==1 && subboard[5] ==1 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==1 && subboard[7] ==1)||
            (subboard[3] ==1 && subboard[5] ==2 && subboard[7] ==1)
        ){O_wins++;}
        if(// having 1 O
            (subboard[3] ==1 && subboard[5] ==2 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==1 && subboard[7] ==2)||
            (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==1)
        ){O_wins++;}
        if(//empty
            subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==2
        ){
            X_wins++;
            O_wins++;
        }
        if(//empty
            subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==2
        ){
            X_wins++;
            O_wins++;
        }
        // printf("x:%d, o: %d\n",X_wins,O_wins);
        // int temp = ceil(X_wins*100/(O_wins+X_wins));
        // printf("x/o:%d\n",temp);
        if(X_wins == 0 && O_wins == 0){
            return 50;
        }else{
            return ceil(X_wins*100/(O_wins+X_wins));
        }
    }
}
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
                // printf("x/o:%d\n",alpha);
                // printf("%d\n",alpha);
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
int ChooseMove(int board[10][10],int Performance[10],int prev_move, int player){
    int ArrayOfBMove[10] = {0,0,0,0,0,0,0,0,0,0};
    int Count = 0;
    int BestMove = 0;
    if(player == 0){
        int BScoreX = -1000;
        // get the best performance of X
        for(int i =1; i <10;i++){
            if(Performance[i] > -1){
                if(BScoreX < Performance[i]){
                    BScoreX = Performance[i];
                    BestMove = i;
                }
            }
        }
        printf("BS:%d\n",BScoreX);
        // // must lose when no performance is greater than 0
        // if(BScoreX == -1000){
        //     for(int i =1; i <10;i++){
        //         if(board[prev_move][i] == 2){
        //             return i;
        //         }
        //     }
        // }
        // count the number of moves with the best performance of X
        // and store the moves
        for(int i =1; i <10;i++){
            if(Performance[i] ==  BScoreX){
                ArrayOfBMove[i] = i;
                ArrayOfBMove[0] ++;
                // //prepare for the recursion
                // Performance[i] = -1;
            }
        }
        // choose the one with most Xs in next board
        for(int i=1;i<10;i++){
            if(ArrayOfBMove[i] > 0){
                // theoritcally, board[prev_move][i] = 2;
                board[prev_move][i] = 0;
                //if there are 3Xs
                if(isWon(board[prev_move],0,3) == 1){
                    return i;
                }
                //having the most Xs in next board but dont have ready to win situation
                if(Count < Cal(board[i],0)){
                    Count = Cal(board[i],0);
                    // if(isWon(board[i],1,2) != 1){
                    BestMove = i;
                    // }
                }
                board[prev_move][i] = 2;
            }
        }
        printf("Me X:%d\n",BestMove);
        //
        // if( BestMove == 0){
        //     return ChooseMove(board,Performance,prev_move,player);
        // }
        return BestMove;
    }else
    {
        int BScoreO = 1000;
        // get the best performance of O
        for(int i =1; i <10;i++){
            if(Performance[i] > 0){
                if(BScoreO > Performance[i]){
                    BScoreO = Performance[i];
                    BestMove = i;
                }
            }
        }
        // // must lose when no performance is greater than 0
        // if(BScoreO == 1000){
        //     for(int i =1; i <10;i++){
        //         if(board[prev_move][i] == 2){
        //             return i;
        //         }
        //     }
        // }
        // count the number of moves with the best performance of O
        // and store the moves
        for(int i =1; i <10;i++){
            if(Performance[i] ==  BScoreO){
                ArrayOfBMove[i] = i;
                ArrayOfBMove[0] ++;
                // //prepare for the recursion
                // Performance[i] = -1;
            }
        }
        // choose the one with most Os in next board
        for(int i=1;i<10;i++){
            if(ArrayOfBMove[i] > 0){
                // theoritcally, board[prev_move][i] = 2;
                board[prev_move][i] = 1;
                //if there are 3Os
                if(isWon(board[prev_move],1,3) == 1){
                    return i;
                }
                //having the most Os in next board but dont have ready to win situation
                if(Count < Cal(board[i],1)){
                    Count = Cal(board[i],1);
                    // if(isWon(board[i],0,2) != 1){
                    BestMove = i;
                    // }
                }
                board[prev_move][i] = 2;
            }
        }
        printf("Me O:%d\n",BestMove);
        //
        // if( BestMove == 0){
        //     return ChooseMove(board,Performance,prev_move,player);
        // }
        return BestMove;
    } 
}
int getBestMove(int board[10][10], int prev_move, int depth, int player){
    int val;
    int PerformanceOfX[10] = {0,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int PerformanceOfO[10] = {0,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    if(player == 0){// I am player X
        for(int i = 1; i< 10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = 0;
                val = alphabeta(board,i,depth,AL,BT,!player);
                printf("%d:%d\n",i,val);
                board[prev_move][i] = 2;
                PerformanceOfX[i] = val;
                PerformanceOfX[0]++;
            }
        }
        return ChooseMove(board,PerformanceOfX,prev_move,player);
    }else{ // I am player O
        for(int i = 1; i< 10;i++){
            if(board[prev_move][i] == 2){
                board[prev_move][i] = 1;
                val = alphabeta(board,i,depth,AL,BT,!player);
                printf("%d:%d\n",i,val);
                board[prev_move][i] = 2;
                PerformanceOfO[i] = val;
                PerformanceOfO[0]++;
            }
        }
        return ChooseMove(board,PerformanceOfO,prev_move,player);
    }
}


