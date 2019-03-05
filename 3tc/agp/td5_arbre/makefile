CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: arbreBinaire

arbreBinaire.o: arbreBinaire.c arbreBinaire.h
	gcc ${CFLAGS} -c arbreBinaire.c -o arbreBinaire.o

main.o: main.c
	gcc ${CFLAGS} -c main.c -o main.o

arbreBinaire: arbreBinaire.o main.o
	gcc ${LDFLAGS} main.o arbreBinaire.o -o arbreBinaire

clean: 
	\rm -rf *.o *~
