all: clean tp0.out

TAD/pilhaOperacoes.o: TAD/pilhaOperacoes.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/pilhaOperacoes.c -o TAD/pilhaOperacoes.o

TAD/filaNumeros.o: TAD/filaNumeros.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/filaNumeros.c -o TAD/filaNumeros.o

TAD/possibilidades.o: TAD/possibilidades.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c TAD/possibilidades.c -o TAD/possibilidades.o

tp0.out: TAD/filaNumeros.o TAD/pilhaOperacoes.o TAD/possibilidades.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp0.out TAD/filaNumeros.o TAD/pilhaOperacoes.o TAD/possibilidades.o -lm

clean:
	-rm -f tp0.out
	-rm -f TAD/filaNumeros.o
	-rm -f TAD/pilhaOperacoes.o
	-rm -f TAD/possibilidades.o
