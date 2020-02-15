all: tp0.out

tp0.out: Functions/generalFunctions.o ADT/Player/player.o
	gcc -w main.c -o tp0.out Functions/generalFunctions.o ADT/Player/player.o

ADT/Player/player.o: ADT/Player/player.c
	gcc -c ADT/Player/player.c -o ADT/Player/player.o

Functions/generalFunctions.o: Functions/generalFunctions.c
	gcc -c Functions/generalFunctions.c -o Functions/generalFunctions.o

clean:
	-rm -f Functions/generalFunctions.o
	-rm -f tp0.out
	-rm -f ADT/Player/player.o
