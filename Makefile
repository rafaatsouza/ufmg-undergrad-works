all: clean tp0.out

TAD/pilhaOperacoes.o: TAD/pilhaOperacoes.c
	gcc -c TAD/pilhaOperacoes.c -o TAD/pilhaOperacoes.o

TAD/filaNumeros.o: TAD/filaNumeros.c
	gcc -c TAD/filaNumeros.c -o TAD/filaNumeros.o

tp0.out: TAD/pilhaOperacoes.o TAD/filaNumeros.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp0.out TAD/pilhaOperacoes.o TAD/filaNumeros.o

clean:
	-rm -f tp0.out
	-rm -f TAD/filaNumeros.o
	-rm -f TAD/pilhaOperacoes.o
