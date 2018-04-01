all: part2

part2: desfunct.o part2.o 
		g++ desfunct.o part2.o -o part2

part2.o: part2.cpp desfunct.h
		g++ -c part2.cpp

desfunct.o:	desfunct.cpp desfunct.h
				g++ -c desfunct.cpp
