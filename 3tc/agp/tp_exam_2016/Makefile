FLAGS = -Wall -g -DDEBUG

all: array

array: array.o main.o
	gcc ${FLAGS} $^ -o $@

array.o: array.c array.h
	gcc ${FLAGS} -c $< -o $@

main.o: main.c
	gcc ${FLAGS} -c $< -o $@
