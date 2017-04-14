all: clean tp0.out

tp0.out: TAD/filaNumeros.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp0.out TAD/filaNumeros.o

TAD/filaNumeros.o: TAD/filaNumeros.c
	gcc -c TAD/filaNumeros.c -o TAD/filaNumeros.o

clean:
	-rm -f tp0.out
	-rm -f TAD/filaNumeros.o
