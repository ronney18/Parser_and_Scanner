

test: parse.o scan.o
	g++ -o test parse.o scan.o

clean:
	rm *.o test

parse.o: scan.h
	g++ -c parse.cpp -Wall -Werror -ansi -pedantic -std=c++11

scan.o: scan.h
	g++ -c scan.cpp -Wall -Werror -ansi -pedantic -std=c++11

