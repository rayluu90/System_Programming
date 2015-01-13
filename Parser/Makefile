###########################################################
# Programmers: Ray Luu
# Username: masc0720
# CS530, Fall 2013
# Instructor: Guy Leonard
# Assignment 3
# Due Date: December 9, 2013
# Makefile 
###########################################################

CC = g++
CFLAGS = -g
LDFLAGS = -lm

bnf : main.o Parser.o Table.o 
	${CC} ${CFLAGS} Parser.o Table.o main.o ${LDFLAGS} -o bnf

Parser.o : Parser.cpp
	${CC} ${CFLAGS} -c Parser.cpp

Table.o : Table.cpp 
	${CC} ${CFLAGS} -c Table.cpp
	
main.o : main.cpp
	${CC} ${CFLAGS} -c main.cpp

clean: 
	rm -f bnf *.o
