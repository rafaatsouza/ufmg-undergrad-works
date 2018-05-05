all: clean tp2.out

tp2.out: stringMethods.o movieJson.o movies.o
	g++ -Wall -Wextra -std=c++11 main.cpp -o tp2.out stringMethods.o movieJson.o movies.o -O3

stringMethods.o: stringMethods.cpp
	g++ -Wall -Wextra -std=c++11 -c stringMethods.cpp -o stringMethods.o -O3

movies.o: movies.cpp
	g++ -Wall -Wextra -std=c++11 -c movies.cpp -o movies.o -O3

movieJson.o: movieJson.cpp
	g++ -Wall -Wextra -std=c++11 -c movieJson.cpp -o movieJson.o -O3

clean:
	-rm -f Tests/submission.csv
	-rm -f tp2.out
	-rm -f movies.o
	-rm -f stringMethods.o
	-rm -f movieJson.o
