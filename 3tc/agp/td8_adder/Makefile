CFLAGS = -Wall -g -DDEBUG

all: adder

lex.yy.c: adder.l
	flex $<

adder.tab.c: adder.y
	bison -d $<

adder: lex.yy.c adder.tab.c
	gcc $^ -o $@ ${CFLAGS}

clean:
	rm adder.tab.*
	rm lex*
