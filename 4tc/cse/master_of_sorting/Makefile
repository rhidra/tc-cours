FLAGS = -g -Wall -DDEBUG

all: sort

sort.o:	sort.c sort.h
	gcc ${FLAGS} -c sort.c -o sort.o

sort: sort.o
	gcc ${FLAGS} sort.o -o mp2_20180326 -lm

clean:
	\rm -rf *.o *~
	rm mp2_20180326
