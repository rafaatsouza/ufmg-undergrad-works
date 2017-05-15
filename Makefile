all: clean tp1.out

grafo.o: grafo.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c grafo.c -o grafo.o

tp1.out: grafo.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp1.out grafo.o -lm

clean:
	-rm -f tp1.out
	-rm -f grafo.o
