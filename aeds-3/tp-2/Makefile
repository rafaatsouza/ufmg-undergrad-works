all: clean tp2.out

tp2.out: index.o fitas.o
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp2.out index.o fitas.o -lm

index.o: index.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c index.c -o index.o

fitas.o: fitas.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c fitas.c -o fitas.o

clean:
	-rm -f tp2.out
	-rm -f index.o
	-rm -f fitas.o
