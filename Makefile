all: clean tp1.out

fila.o: fila.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c fila.c -o fila.o

grafo.o: fila.o grafo.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c grafo.c -o grafo.o fila.o

tp1.out: fila.o grafo.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp1.out fila.o grafo.o -lm

clean:
	-rm -f tp1.out
	-rm -f fila.o
	-rm -f grafo.o
