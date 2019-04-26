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
//version3:
possible wins: X/O *100
100 means X wins
0 means O wins

//version4:
possible wins of target(having 2/3 in a row/column/diagnose)
*/
//Eval version 4
int Eval(int subboard[10],int target){
    int wins = 0;
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
    ){wins++;}
    // rows
    for(int i = 1; i<10;i = i+3){
        if(// having 2 Xs
            (subboard[i] ==target && subboard[i+1] ==target && subboard[i+2] ==2)||
            (subboard[i] ==2 && subboard[i+1] ==target && subboard[i+2] ==target)||
            (subboard[i] ==target && subboard[i+1] ==2 && subboard[i+2] ==target)
        ){wins++;}
        if(// having 1 X
            (subboard[i] ==target && subboard[i+1] ==2 && subboard[i+2] ==2)||
            (subboard[i] ==2 && subboard[i+1] ==target && subboard[i+2] ==2)||
            (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==target)
        ){wins = wins + 0.5;}
        // empty row
        if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
            wins = wins + 0.5;
        }
    }
    //columns
    for(int i = 1; i<4;i++){
        if(// having 2 Xs
            (subboard[i] ==target && subboard[i+3] ==target && subboard[i+6] ==2)||
            (subboard[i] ==2 && subboard[i+3] ==target && subboard[i+6] ==target)||
            (subboard[i] ==target && subboard[i+3] ==2 && subboard[i+6] ==target)
        ){wins++;}
        if(// having 1 X
            (subboard[i] ==target && subboard[i+3] ==2 && subboard[i+6] ==2)||
            (subboard[i] ==2 && subboard[i+3] ==target && subboard[i+6] ==2)||
            (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==target)
        ){wins = wins + 0.5;}
        // empty row
        if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
            wins = wins + 0.5;
        }
    }
    //diagnoses
    if(// having 2 Xs
        (subboard[1] ==target && subboard[5] ==target && subboard[9] ==2)||
        (subboard[1] ==2 && subboard[5] ==target && subboard[9] ==target)||
        (subboard[1] ==target && subboard[5] ==2 && subboard[9] ==target)
    ){wins++;}
    if(//having 1 X
        (subboard[1] ==target && subboard[5] ==2 && subboard[9] ==2)||
        (subboard[1] ==2 && subboard[5] ==target && subboard[9] ==2)||
        (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==target)
    ){wins = wins + 0.5;}
    if(// having 2 Xs
        (subboard[3] ==target && subboard[5] ==target && subboard[7] ==2)||
        (subboard[3] ==2 && subboard[5] ==target && subboard[7] ==target)||
        (subboard[3] ==target && subboard[5] ==2 && subboard[7] ==target)
    ){wins++;}
    if(// having 1 X
        (subboard[3] ==target && subboard[5] ==2 && subboard[7] ==2)||
        (subboard[3] ==2 && subboard[5] ==target && subboard[7] ==2)||
        (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==target)
    ){wins = wins + 0.5;}
    if(//empty
        subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==2
    ){
        wins = wins + 0.5;
    }
    if(//empty
        subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==2
    ){
        wins = wins + 0.5;
    }
    return wins*10;
}
//Eval version 3
// int Eval(int subboard[10],int target){
//     int X_wins = 0;
//     int O_wins = 0;
//     if(
//         //columns
//         (subboard[1] == 0 && subboard[4] == 0 && subboard[7] == 0)||
//         (subboard[2] == 0 && subboard[5] == 0 && subboard[8] == 0)||
//         (subboard[3] == 0 && subboard[6] == 0 && subboard[9] == 0)||
//         //rows
//         (subboard[1] == 0 && subboard[2] == 0 && subboard[3] == 0)||
//         (subboard[4] == 0 && subboard[5] == 0 && subboard[6] == 0)||
//         (subboard[7] == 0 && subboard[8] == 0 && subboard[9] == 0)||
//         //diagnoses
//         (subboard[1] == 0 && subboard[5] == 0 && subboard[9] == 0)||
//         (subboard[3] == 0 && subboard[5] == 0 && subboard[7] == 0)
//     ){return 100;}
//     else if(
//         //columns
//         (subboard[1] == 1 && subboard[4] == 1 && subboard[7] == 1)||
//         (subboard[2] == 1 && subboard[5] == 1 && subboard[8] == 1)||
//         (subboard[3] == 1 && subboard[6] == 1 && subboard[9] == 1)||
//         //rows
//         (subboard[1] == 1 && subboard[2] == 1 && subboard[3] == 1)||
//         (subboard[4] == 1 && subboard[5] == 1 && subboard[6] == 1)||
//         (subboard[7] == 1 && subboard[8] == 1 && subboard[9] == 1)||
//         //diagnoses
//         (subboard[1] == 1 && subboard[5] == 1 && subboard[9] == 1)||
//         (subboard[3] == 1 && subboard[5] == 1 && subboard[7] == 1)
//     ){return 0;}
//     else{
//         // rows
//         for(int i = 1; i<10;i = i+3){
//             if(// having 2 Xs
//                 (subboard[i] ==0 && subboard[i+1] ==0 && subboard[i+2] ==2)||
//                 (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==0)||
//                 (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==0)
//             ){X_wins++;}
//             if(// having 1 X
//                 (subboard[i] ==0 && subboard[i+1] ==2 && subboard[i+2] ==2)||
//                 (subboard[i] ==2 && subboard[i+1] ==0 && subboard[i+2] ==2)||
//                 (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==0)
//             ){X_wins++;}
//             if(// having 2 Os
//                 (subboard[i] ==1 && subboard[i+1] ==1 && subboard[i+2] ==2)||
//                 (subboard[i] ==2 && subboard[i+1] ==1 && subboard[i+2] ==1)||
//                 (subboard[i] ==1 && subboard[i+1] ==2 && subboard[i+2] ==1)
//             ){O_wins++;}
//             if(// having 1 O
//                 (subboard[i] ==1 && subboard[i+1] ==2 && subboard[i+2] ==2)||
//                 (subboard[i] ==2 && subboard[i+1] ==1 && subboard[i+2] ==2)||
//                 (subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] ==1)
//             ){O_wins++;}
//             // empty row
//             if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
//                 X_wins++;
//                 O_wins++;
//             }
//         }
//         //columns
//         for(int i = 1; i<4;i++){
//             if(// having 2 Xs
//                 (subboard[i] ==0 && subboard[i+3] ==0 && subboard[i+6] ==2)||
//                 (subboard[i] ==2 && subboard[i+3] ==0 && subboard[i+6] ==0)||
//                 (subboard[i] ==0 && subboard[i+3] ==2 && subboard[i+6] ==0)
//             ){X_wins++;}
//             if(// having 1 X
//                 (subboard[i] ==0 && subboard[i+3] ==2 && subboard[i+6] ==2)||
//                 (subboard[i] ==2 && subboard[i+3] ==0 && subboard[i+6] ==2)||
//                 (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==0)
//             ){X_wins++;}
//             if(// having 2 Os
//                 (subboard[i] ==1 && subboard[i+3] ==1 && subboard[i+6] ==2)||
//                 (subboard[i] ==2 && subboard[i+3] ==1 && subboard[i+6] ==1)||
//                 (subboard[i] ==1 && subboard[i+3] ==2 && subboard[i+6] ==1)
//             ){O_wins++;}
//             if(// having 1 O
//                 (subboard[i] ==1 && subboard[i+3] ==2 && subboard[i+6] ==2)||
//                 (subboard[i] ==2 && subboard[i+3] ==1 && subboard[i+6] ==2)||
//                 (subboard[i] ==2 && subboard[i+3] ==2 && subboard[i+6] ==1)
//             ){O_wins++;}
//             // empty row
//             if(subboard[i] ==2 && subboard[i+1] ==2 && subboard[i+2] == 2){
//                 X_wins++;
//                 O_wins++;
//             }
//         }
//         //diagnoses
//         if(// having 2 Xs
//             (subboard[1] ==0 && subboard[5] ==0 && subboard[9] ==2)||
//             (subboard[1] ==2 && subboard[5] ==0 && subboard[9] ==0)||
//             (subboard[1] ==0 && subboard[5] ==2 && subboard[9] ==0)
//         ){X_wins++;}
//         if(//having 1 X
//             (subboard[1] ==0 && subboard[5] ==2 && subboard[9] ==2)||
//             (subboard[1] ==2 && subboard[5] ==0 && subboard[9] ==2)||
//             (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==0)
//         ){X_wins++;}
//         if(// having 2 Xs
//             (subboard[3] ==0 && subboard[5] ==0 && subboard[7] ==2)||
//             (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==0)||
//             (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==0)
//         ){X_wins++;}
//         if(// having 1 X
//             (subboard[3] ==0 && subboard[5] ==2 && subboard[7] ==2)||
//             (subboard[3] ==2 && subboard[5] ==0 && subboard[7] ==2)||
//             (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==0)
//         ){X_wins++;}
//         if(// having 2 Os
//             (subboard[1] ==1 && subboard[5] ==1 && subboard[9] ==2)||
//             (subboard[1] ==2 && subboard[5] ==1 && subboard[9] ==1)||
//             (subboard[1] ==1 && subboard[5] ==2 && subboard[9] ==1)
//         ){O_wins++;}
//         if(//having 1 O
//             (subboard[1] ==1 && subboard[5] ==2 && subboard[9] ==2)||
//             (subboard[1] ==2 && subboard[5] ==1 && subboard[9] ==2)||
//             (subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==1)
//         ){O_wins++;}
//         if(// having 2 Os
//             (subboard[3] ==1 && subboard[5] ==1 && subboard[7] ==2)||
//             (subboard[3] ==2 && subboard[5] ==1 && subboard[7] ==1)||
//             (subboard[3] ==1 && subboard[5] ==2 && subboard[7] ==1)
//         ){O_wins++;}
//         if(// having 1 O
//             (subboard[3] ==1 && subboard[5] ==2 && subboard[7] ==2)||
//             (subboard[3] ==2 && subboard[5] ==1 && subboard[7] ==2)||
//             (subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==1)
//         ){O_wins++;}
//         if(//empty
//             subboard[1] ==2 && subboard[5] ==2 && subboard[9] ==2
//         ){
//             X_wins++;
//             O_wins++;
//         }
//         if(//empty
//             subboard[3] ==2 && subboard[5] ==2 && subboard[7] ==2
//         ){
//             X_wins++;
//             O_wins++;
//         }
//         // printf("x:%d, o: %d\n",X_wins,O_wins);
//         // int temp = ceil(X_wins*100/(O_wins+X_wins));
//         // printf("x/o:%d\n",temp);
//         if(X_wins == 0 && O_wins == 0){
//             return 50;
//         }else{
//             return ceil(X_wins*100/(O_wins+X_wins));
//         }
//     }
// }
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
        return Eval(board[prev_move],Player);
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
    int PerformanceOfX[10] = {0,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    BinomialHeap * PQ1 = newHeap();
        // if(Cal(board[prev_move],2) == 9 && Cal(board[5],0) == 0){
        //     return 5;
        // }
    for(int i = 1; i< 10;i++){
        if(board[prev_move][i] == 2){
            board[prev_move][i] = player;
            val = alphabeta(board,i,depth,AL,BT,!player);
            printf("%d:%d\n",i,val);
            board[prev_move][i] = 2;
            Insert(PQ1,val,i,0,0,0);
        }
    }
    for(int i = PerformanceOfX[0]+1; i <10;i++){
        if(PQ1->smallestB == NULL){break;}
        PerformanceOfX[i] = RemoveMin(PQ1)->TaskName;
        PerformanceOfX[0] ++;
    }

    if(PerformanceOfX[0]==1){
        printf("1X\n");
        return PerformanceOfX[1];
    }else{
        if(player == 0){
            //reversed visiting the array
            for(int j= PerformanceOfX[0]; j>0 ;j--){
                // if win after this move, then choose it first
                //otherwise, if this move bolcks, and dont lose in next board, then choose it
                board[prev_move][PerformanceOfX[j]] = player;
                // win at this step
                if(isWon(board[prev_move],player,3) == 1){
                    board[prev_move][PerformanceOfX[j]] = 2;
                    return PerformanceOfX[j];
                }else{
                    //blcking(but not really blocking)
                    board[prev_move][PerformanceOfX[j]] = 2;
                    if(Blocking(board[prev_move],!player,PerformanceOfX[j]) == 1 && isWon(board[PerformanceOfX[j]],!player,2) != 1){
                        printf("bb X\n");
                        return PerformanceOfX[j];
                    }else{
                        board[prev_move][PerformanceOfX[j]] = player;
                        if(isWon(board[PerformanceOfX[j]],!player,2)!=1){
                            board[prev_move][PerformanceOfX[j]] = 2;
                            printf("2X\n");
                            return PerformanceOfX[j];
                        }
                        board[prev_move][PerformanceOfX[j]] = 2;
                    }
                }
            }
        }else{
            for(int j=1; j<= PerformanceOfX[0]; j++){
                // if win after this move, then choose it first
                //otherwise, if this move bolcks, and dont lose in next board, then choose it
                board[prev_move][PerformanceOfX[j]] = player;
                // win at this step
                if(isWon(board[prev_move],player,3) == 1){
                    board[prev_move][PerformanceOfX[j]] = 2;
                    return PerformanceOfX[j];
                }else{
                    //blcking(but not really blocking)
                    board[prev_move][PerformanceOfX[j]] = 2;
                    if(Blocking(board[prev_move],!player,PerformanceOfX[j]) == 1 && isWon(board[PerformanceOfX[j]],!player,2) != 1){
                        printf("bb X\n");
                        return PerformanceOfX[j];
                    }else{
                        board[prev_move][PerformanceOfX[j]] = player;
                        if(isWon(board[PerformanceOfX[j]],!player,2)!=1){
                            board[prev_move][PerformanceOfX[j]] = 2;
                            printf("2X\n");
                            return PerformanceOfX[j];
                        }
                        board[prev_move][PerformanceOfX[j]] = 2;
                    }
                }
            }
        }
        printf("3X\n");
        return PerformanceOfX[PerformanceOfX[0]];
    }
}


