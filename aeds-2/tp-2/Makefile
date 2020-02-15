all: clean tp2.out

tp2.out: Funcoes/Ordena.o
	gcc -w main.c -o tp2.out Funcoes/Ordena.o

Funcoes/Ordena.o: Funcoes/Ordena.c
	gcc -c Funcoes/Ordena.c -o Funcoes/Ordena.o

clean:
	-rm -f tp2.out
	-rm -f Funcoes/Ordena.o
