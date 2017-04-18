all: clean tp0.out

TAD/pilhaOperacoes.o: TAD/pilhaOperacoes.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/pilhaOperacoes.c -o TAD/pilhaOperacoes.o

TAD/filaNumeros.o: TAD/filaNumeros.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/filaNumeros.c -o TAD/filaNumeros.o

Functions/possibilidades.o: Functions/possibilidades.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c Functions/possibilidades.c -o Functions/possibilidades.o

tp0.out: TAD/filaNumeros.o TAD/pilhaOperacoes.o Functions/possibilidades.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp0.out TAD/filaNumeros.o TAD/pilhaOperacoes.o Functions/possibilidades.o -lm

clean:
	-rm -f tp0.out
	-rm -f TAD/filaNumeros.o
	-rm -f TAD/pilhaOperacoes.o
	-rm -f Functions/possibilidades.o
