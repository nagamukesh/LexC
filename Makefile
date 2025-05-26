CC=gcc
CFLAGS=-Wall

# Default build
all: compiler

# Debug build with address sanitizer
debug: CFLAGS += -g -fsanitize=address -fno-omit-frame-pointer
debug: compiler

# Memory leak check build
memcheck: CFLAGS += -g
memcheck: compiler

# Thread sanitizer build
thread: CFLAGS += -g -fsanitize=thread
thread: compiler

# Undefined behavior sanitizer
undefined: CFLAGS += -g -fsanitize=undefined
undefined: compiler

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

.PHONY: all debug memcheck thread undefined clean