all: clean tp2.out

tp2.out: 
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp2.out -lm

clean:
	-rm -f tp2.out
