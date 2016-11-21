all: clean tp2.out

tp2.out: Funções/Funcoes.o
	gcc -w main.c -o tp2.out Funções/Funcoes.o

Funções/Funcoes.o: Funções/Funcoes.c
	gcc -c Funções/Funcoes.c -o Funções/Funcoes.o

clean:
	-rm -f tp2.out
	-rm -f Funções/Funcoes.o
