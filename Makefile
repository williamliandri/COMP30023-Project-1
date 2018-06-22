# # # # # # #
# Makefile for Project 1 Computer System
# 
# Author: William Liandri
# Student ID: 728710
# 


CC = gcc
CFLAGS = -Wall
RM = rm -f
EXE = server
LIBS = -lrt
OBJ = server.o functions.o

# MAIN PROGRAM
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

server.o: libraries.h functions.h
functions.o: libraries.h struct.h

# CLEANING TARGETS
clean:
	$(RM) server
	$(RM) server.o
	$(RM) functions.o
