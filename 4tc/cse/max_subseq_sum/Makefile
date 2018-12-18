FLAGS = -g -Wall -DDEBUG

all: mss

mss.o:	mss.c mss.h
	gcc ${FLAGS} -c mss.c -o mss.o

mss: mss.o
	gcc ${FLAGS} mss.o -o mss20180326

clean:
	\rm -rf *.o *~
	rm mss20180326
