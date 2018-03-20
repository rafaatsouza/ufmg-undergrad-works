all: clean tp1.out

tp1.out: movies.o
	g++ main.cpp -o tp1.out movies.o

movies.o: movies.c
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic -c movies.c -o movies.o

clean:
	-rm -f tp1.out
	-rm -f movies.o
