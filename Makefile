all: clean tp2.out

tp2.out: movies.o
	g++ -Wall -Wextra -std=c++11 main.cpp -o tp2.out movies.o -O3

movies.o: movies.cpp
	g++ -Wall -Wextra -std=c++11 -c movies.cpp -o movies.o -O3

clean:
	-rm -f Tests/submission.csv
	-rm -f tp2.out
	-rm -f movies.o
