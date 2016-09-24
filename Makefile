all: tp0.out

tp0.out: Functions/generalFunctions.o ADT/Player/player.o ADT/Pokemon/pokemon.o
	gcc main.c -o tp0.out Functions/generalFunctions.o ADT/Player/player.o ADT/Pokemon/pokemon.o

ADT/Player/player.o: ADT/Player/player.c
	gcc -c ADT/Player/player.c -o ADT/Player/player.o

ADT/Pokemon/pokemon.o: ADT/Pokemon/pokemon.c
	gcc -c ADT/Pokemon/pokemon.c -o ADT/Pokemon/pokemon.o

Functions/generalFunctions.o: Functions/generalFunctions.c
	gcc -c Functions/generalFunctions.c -o Functions/generalFunctions.o

clean:
	-rm -f Functions/generalFunctions.o
	-rm -f tp0.out
	-rm -f ADT/Player/player.o
	-rm -f ADT/Pokemon/pokemon.o
