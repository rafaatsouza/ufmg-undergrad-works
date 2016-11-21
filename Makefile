all: clean tp2.out

tp2.out: Funcoes/Funcoes.o
	gcc -w main.c -o tp2.out Funcoes/Funcoes.o

Funcoes/Funcoes.o: Funcoes/Funcoes.c
	gcc -c Funcoes/Funcoes.c -o Funcoes/Funcoes.o

clean:
	-rm -f tp2.out
	-rm -f Funcoes/Funcoes.o
