/*********************************************************
 *  agent.c
 *  Nine-Board Tic-Tac-Toe Agent
 *  COMP3411/9414/9814 Artificial Intelligence
 *  Alan Blair, YAOYE LU, CSE, UNSW
*********************************************************
DESCRIPTION:
>> Main idea:
Firstly, the main idea of completing this assignment is using the supplied "agent.c" as a starting pointer 
by generating an integer number(1 - 9) as the next move of my player. This intege number will go to the variable "this move" in the functions of 
agent_second_move, agent_third_move and agent_next_move without changing other parts. This idea is figured out after reading through this file.

>> Framework:
My source code consists of three c files: agent.c, alpha_beta_search.c, BinomialHeapPQ.c
1. agent.c file is for that my player can work.
2. alpha_beta_search.c file is for getting the best move.
3. BinomialHeapPQ.c file is just the implementation of Binomial-Heap based Priority Queue (BHPQ) used in "alpha_beta_search.c".

>> Data Structure:
Binomial-Heap based Priority Queue(self-implemented), int array, int

>> Algorithm:
  >> Alpha-beta search
  I mainly use alpha-beta search to find the best move, but given this is a nine-boards tic-tac-toe, so I made a little adjustment about this algorithm
  when implementing it, which is when go to the next depth, I will go the next board instead of staying in the current board.
    
    >> Heuristic:
    I calculate a score for the target player in a subboard with the following rules:
      (1) If there is a blocking of a 2 !target player, counts 1
      (2) If there are 2 target players in a row/column/diagnose, counts 1
      (3) If there is 1 target player in a row/column/diagnose, counts 0.2
      (The reason to set rule (3) a score of 0.2 is trying to reduce the impact on weight in the final score)
      Then, I go through every diagnose, row and column to sum up the score, and return 10 times of that score (then no need to worry about converting between double and int data types).
    
  >> Priority Queue Sorting
    Using its built-in function "RemoveMin()", this function will return the node with the smallest key.
    So just call this function and insert the corresponing move into an int array to achieve sorting.

>> How it works:
  >> In BinomialHeapPQ.c:
  This part of code is a part of my own code from other subjects, which is the implementation of a binomial-heap based Priority Queue ABS.
  >> In alpha_beta_search.c:
  There are 7 functions in this file --  Eval(), Blocking(), Cal(), isWon(), isFull(), alphabeta(), getBestMove()
  Idea is:
  1. Use alphabeta() to calculate a performance score for each possible move with a for loop and store in binomial-heap based Priority Queue(BHPQ)
  2. Use PQ sorting to sort the performance score in a increasing order and store the corresponding move in an int array
  3. Loop through the int array reversally or not depending on which the player I am
  4. Before deciding a move, I will see 
    4.1 if it wins after I made this move, then choose this move
    4.2 otherwise, I will see if board[this_move] have 2 opponents in any row/column/diagnose, then continue the loop, otherwise, choose this move.
    4.3 if the loop is done, and I did not make a choice, then choose the last move in the int array. 

>> Following the requirement of "briefly answer", for specific function purpose, please go to comments in "alpha_beta_search.c".
*********************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "common.h"
#include "agent.h"
#include "game.h"
#include "alpha_beta_search.c"

#define MAX_MOVE 81
#define DEPTH 6

int board[10][10];
int move[MAX_MOVE+1];
int player;
int m;

/*********************************************************//*
   Print usage information and exit
*/
void usage( char argv0[] )
{
  printf("Usage: %s\n",argv0);
  printf("       [-p port]\n"); // tcp port
  printf("       [-h host]\n"); // tcp host
  exit(1);
}

/*********************************************************//*
   Parse command-line arguments
*/
void agent_parse_args( int argc, char *argv[] )
{
  int i=1;
  while( i < argc ) {
    if( strcmp( argv[i], "-p" ) == 0 ) {
      if( i+1 >= argc ) {
        usage( argv[0] );
      }
      port = atoi(argv[i+1]);
      i += 2;
    }
    else if( strcmp( argv[i], "-h" ) == 0 ) {
      if( i+1 >= argc ) {
        usage( argv[0] );
      }
      host = argv[i+1];
      i += 2;
    }
    else {
      usage( argv[0] );
    }
  }
}

/*********************************************************//*
   Called at the beginning of a series of games
*/
void agent_init()
{
  struct timeval tp;

  // generate a new random seed each time
  gettimeofday( &tp, NULL );
  srandom(( unsigned int )( tp.tv_usec ));
}

/*********************************************************//*
   Called at the beginning of each game
*/
void agent_start( int this_player )
{
  reset_board( board );
  m = 0;
  move[m] = 0;
  player = this_player;
}

/*********************************************************//*
   Choose second move and return it
*/
int agent_second_move( int board_num, int prev_move )
{
  int this_move;
  int BM;
  move[0] = board_num;
  move[1] = prev_move;
  board[board_num][prev_move] = !player;
  m = 2;
  do {
    //my code goes here
    BM = getBestMove(board,prev_move,DEPTH,player);
    this_move = BM;
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  board[prev_move][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Choose third move and return it
*/
int agent_third_move(
                     int board_num,
                     int first_move,
                     int prev_move
                    )
{
  int this_move;
  int BM;
  move[0] = board_num;
  move[1] = first_move;
  move[2] = prev_move;
  board[board_num][first_move] =  player;
  board[first_move][prev_move] = !player;
  m=3;
  do {
    //my code goes here
    BM = getBestMove(board,prev_move,DEPTH,player);
    this_move = BM;
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  board[move[m-1]][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Choose next move and return it
*/
int agent_next_move( int prev_move )
{
  int this_move;
  int BM;
  m++;
  move[m] = prev_move;
  board[move[m-1]][move[m]] = !player;
  // printf("opponent: %d\n",!player);
  m++;
  do {
    //my code goes here
    BM = getBestMove(board,prev_move,DEPTH,player);
    this_move = BM;
  } while( board[prev_move][this_move] != EMPTY );
  move[m] = this_move;
  board[move[m-1]][this_move] = player;
  return( this_move );
}

/*********************************************************//*
   Receive last move and mark it on the board
*/
void agent_last_move( int prev_move )
{
  m++;
  move[m] = prev_move;
  board[move[m-1]][move[m]] = !player;
}

/*********************************************************//*
   Called after each game
*/
void agent_gameover(
                    int result,// WIN, LOSS or DRAW
                    int cause  // TRIPLE, ILLEGAL_MOVE, TIMEOUT or FULL_BOARD
                   )
{
  // nothing to do here
}

/*********************************************************//*
   Called after the series of games
*/
void agent_cleanup()
{
  // nothing to do here
}
