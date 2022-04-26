all: main

main: main.o NumberGenerator.o
	g++ main.o NumberGenerator.o -g -o prog
main.o: main.cpp NumberGenerator.h
	g++ -c -g main.cpp 
NumberGenerator.o: NumberGenerator.cpp NumberGenerator.h
	g++ -c -g NumberGenerator.cpp
clean:
	rm -f *.o prog