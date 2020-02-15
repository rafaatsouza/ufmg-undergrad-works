all: clean tp3.out

tp3.out: vizinhanca.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp3.out vizinhanca.o -lm

vizinhanca.o: vizinhanca.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c vizinhanca.c -o vizinhanca.o

clean:
	-rm -f tp3.out
	-rm -f vizinhanca.o
