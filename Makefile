all: tp1.out

tp1.out: TAD/Usuario/usuario.o TAD/Amizade/amizade.o Funcoes/funcoes.o
	gcc -w main.c -o tp1.out TAD/Usuario/usuario.o TAD/Amizade/amizade.o Funcoes/funcoes.o

TAD/Usuario/usuario.o: TAD/Usuario/usuario.c
		gcc -c TAD/Usuario/usuario.c -o TAD/Usuario/usuario.o

TAD/Amizade/amizade.o: TAD/Amizade/amizade.c
		gcc -c TAD/Amizade/amizade.c -o TAD/Amizade/amizade.o

Funcoes/funcoes.o: Funcoes/funcoes.c
				gcc -c Funcoes/funcoes.c -o Funcoes/funcoes.o

clean:
	-rm -f tp1.out
	-rm -f TAD/Usuario/usuario.o
	-rm -f TAD/Amizade/amizade.o
	-rm -f Funcoes/funcoes.o
