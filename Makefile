all: clean tp1.out

tp1.out: movies.o
	g++ main.cpp -o tp1.out movies.o

movies.o: movies.cpp
	g++ -std=c++11 -c movies.cpp -o movies.o

clean:
	-rm -f tp1.out
	-rm -f movies.o
