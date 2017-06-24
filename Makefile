all: clean tp3.out

tp3.out:
	gcc -w -Wall -Wextra -Werror -std=c99 -pedantic main.c -o tp3.out -lm

clean:
	-rm -f tp3.out
