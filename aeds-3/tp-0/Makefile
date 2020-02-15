all: clean tp0.out

TAD/pilhaOperacoes.o: TAD/pilhaOperacoes.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/pilhaOperacoes.c -o TAD/pilhaOperacoes.o

TAD/filaElementos.o: TAD/filaElementos.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/filaElementos.c -o TAD/filaElementos.o

Functions/possibilidades.o: Functions/possibilidades.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c Functions/possibilidades.c -o Functions/possibilidades.o

tp0.out: TAD/filaElementos.o TAD/pilhaOperacoes.o Functions/possibilidades.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp0.out TAD/filaElementos.o TAD/pilhaOperacoes.o Functions/possibilidades.o -lm

clean:
	-rm -f tp0.out
	-rm -f TAD/filaElementos.o
	-rm -f TAD/pilhaOperacoes.o
	-rm -f Functions/possibilidades.o
