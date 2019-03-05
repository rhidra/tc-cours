FLAGS = -g -Wall -DDEBUG

all: hubert resto user

# Hubert

hubert.o:	hubert.c hubert.h
	gcc ${FLAGS} -c hubert.c -o hubert.o

hubert: hubert.o
	gcc ${FLAGS} hubert.o -o hubert

# Resto

resto.o:	resto.c resto.h
	gcc ${FLAGS} -c resto.c -o resto.o

resto: resto.o
	gcc ${FLAGS} resto.o -o resto

# User

user.o:	user.c user.h
	gcc ${FLAGS} -c user.c -o user.o

user: user.o
	gcc ${FLAGS} user.o -o user


clean:
	rm -rf *.o *~ user resto hubert stop_hubert
