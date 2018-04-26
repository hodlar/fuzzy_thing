CC=gcc
LIBS=-lm
fuzzymake: programa.c
	gcc programa.c -o programa $(LIBS) -ggdb
clean:
	rm programa
