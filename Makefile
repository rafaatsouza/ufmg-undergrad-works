all: bomber.out

bomber.out: Functions/functions.o
	gcc -w bomber.c $(pkg-config --libs allegro-5.0 allegro_main-5.0 allegro_primitives-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0) -o bomber.out Functions/functions.o -lpthread -lm

Functions/functions.o: Functions/functions.c
	gcc -c Functions/functions.c -o Functions/functions.o

clean:
	-rm -f Functions/functions.o
	-rm -f bomber.out
