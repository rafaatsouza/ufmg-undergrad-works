all: clean tp1.out

tp1.out: TAD/Amizade/amizade.o TAD/Usuario/usuario.o TAD/Mensagem/mensagem.o
	gcc -w main.c -o tp1.out TAD/Amizade/amizade.o TAD/Usuario/usuario.o TAD/Mensagem/mensagem.o

TAD/Amizade/amizade.o: TAD/Amizade/amizade.c
			gcc -c TAD/Amizade/amizade.c -o TAD/Amizade/amizade.o

TAD/Mensagem/mensagem.o: TAD/Mensagem/mensagem.c
					gcc -c TAD/Mensagem/mensagem.c -o TAD/Mensagem/mensagem.o

TAD/Usuario/usuario.o: TAD/Usuario/usuario.c
		gcc -c TAD/Usuario/usuario.c -o TAD/Usuario/usuario.o

clean:
	-rm -f tp1.out
	-rm -f TAD/Usuario/usuario.o
	-rm -f TAD/Amizade/amizade.o
	-rm -f TAD/Mensagem/mensagem.o
