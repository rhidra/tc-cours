FLAGS = -g -Wall -DDEBUG

all: ex2

list.o: list.c list.h
	gcc ${FLAGS} -c list.c -o list.o

main.o: main.c
	gcc ${FLAGS} -c main.c -o main.o

ex2: list.o main.o
	gcc ${FLAGS} list.o main.o -o $@

clean:
	\rm -f ex1
