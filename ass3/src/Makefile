#  Makefile
#  Nine-Board Tic-Tac-Toe
#  COMP3411/9414/9814 Artificial Intelligence
#  Alan Blair, CSE, UNSW

# CC = gcc
# CFLAGS = -Wall -g -O3

# default: agent

# agent: agent.o client.o game.o common.h agent.h game.h
# 	$(CC) $(CFLAGS) -o agent agent.o client.o game.o

# servt: servt.o game.o common.h game.h agent.h
# 	$(CC) $(CFLAGS) -o servt servt.o game.o

# randt: randt.o client.o game.o common.h agent.h game.h
# 	$(CC) $(CFLAGS) -o randt randt.o client.o game.o

# all: servt randt agent

# %o:%c common.h agent.h
# 	$(CC) $(CFLAGS) -c $<

# clean:
# 	rm -f servt randt agent *.o
output: alpha_beta_search.o
	gcc alpha_beta_search.o  -o output

alpha_beta_search.o: alpha_beta_search.c
	gcc -c alpha_beta_search.c

clean:
	rm -f *.o output