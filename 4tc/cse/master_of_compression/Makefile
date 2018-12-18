FLAGS = -g -Wall -DDEBUG

all: compress

compress.o:	compress.c compress.h param.h
	gcc ${FLAGS} -c compress.c -o compress.o

heap.o:	heap.c heap.h param.h
	gcc ${FLAGS} -c heap.c -o heap.o

compress: heap.o compress.o
	gcc ${FLAGS} compress.o heap.o -o mp3_20180326 -lm

clean:
	\rm -rf *.o *~
	rm mp3_20180326
	rm *.zz *.yy
