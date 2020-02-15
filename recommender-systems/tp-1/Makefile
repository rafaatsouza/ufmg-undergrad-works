all: clean tp1.out

tp1.out: movies.o
	g++ -Wall -Wextra -std=c++11 main.cpp -o tp1.out movies.o -O3

movies.o: movies.cpp
	g++ -Wall -Wextra -std=c++11 -c movies.cpp -o movies.o -O3

clean:
	-rm -f Tests/submission.csv
	-rm -f tp1.out
	-rm -f movies.o
