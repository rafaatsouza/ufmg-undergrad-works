all: clean tp2.out

Funcoes/Funcoes.o: Funcoes/Funcoes.c
	gcc -c Funcoes/Funcoes.c -o Funcoes/Funcoes.o

tp2.out: Funcoes/Ordena.o Funcoes/Funcoes.o
	gcc -w main.c -o tp2.out Funcoes/Funcoes.o Funcoes/Ordena.o

Funcoes/Ordena.o: Funcoes/Ordena.c Funcoes/Funcoes.o
		gcc -c Funcoes/Ordena.c -o Funcoes/Ordena.o Funcoes/Funcoes.o

clean:
	-rm -f tp2.out
	-rm -f Funcoes/Funcoes.o
	-rm -f Funcoes/Ordena.o
