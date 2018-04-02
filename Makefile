all: clean tp1.out

tp1.out: movies.o
	g++ -std=c++11 main.cpp -o tp1.out movies.o -O3

movies.o: movies.cpp
	g++ -std=c++11 -c movies.cpp -o movies.o -O3

clean:
	-rm -f tp1.out
	-rm -f movies.o
