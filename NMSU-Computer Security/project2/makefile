all: project2

project2: desfunct.o project2.o 
		g++ desfunct.o project2.o -o project2

project2.o: project2.cpp desfunct.h
		g++ -c project2.cpp

desfunct.o:	desfunct.cpp desfunct.h
				g++ -c desfunct.cpp
