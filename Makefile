CC=gcc
CFLAGS=-Wall

all: compiler

compiler: lex.yy.c y.tab.c custom_memory.o
	$(CC) $(CFLAGS) -o $@ $^ -lfl

lex.yy.c: final_lexer.l y.tab.h
	flex $<

y.tab.c y.tab.h: final_parser.y
	yacc -d $<

custom_memory.o: custom_memory.c custom_memory.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f compiler lex.yy.c y.tab.c y.tab.h *.o