CC = gcc
CFLAGS = -Wall -g

all: hanoi

hanoi: main.o pile.o hanoi.o
	${CC} ${CFLAGS} main.o pile.o hanoi.o -o hanoi

main.o: main.c pile_type.h pile.h
	${CC} ${CFLAGS} -c main.c -o main.o

pile.o: pile.c pile.h pile_type.h
	${CC} ${CFLAGS} -c pile.c -o pile.o

hanoi.o: hanoi.c hanoi.h
	${CC} ${CFLAGS} -c hanoi.c -o hanoi.o

clean:
	rm *.o

test: test.o pile.o
	${CC} ${CFLAGS} test.o pile.o -o test

test.o: test.c
	${CC} ${CFLAGS} -c test.c -o test.o
