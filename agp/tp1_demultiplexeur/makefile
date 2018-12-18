CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: demultiplexeur 

demultiplexeur.o:	demultiplexeur.c
	gcc ${CFLAGS} -c demultiplexeur.c -o demultiplexeur.o

demultiplexeur: demultiplexeur.o 
	gcc ${LDFLAGS} demultiplexeur.o -o demultiplexeur

clean: 
	\rm -rf *.o *~
