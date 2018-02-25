all: part1

part1: cipherfunct.o part1.o 
		g++ cipherfunct.o part1.o -o part1

part1.o: part1.cpp cipherfunct.h
		g++ -c part1.cpp

cipherfunct.o:	cipherfunct.cpp cipherfunct.h
				g++ -c cipherfunct.cpp