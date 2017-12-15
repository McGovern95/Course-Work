all: testComplex

testComplex: Complex.o testComplex.o
				g++ Complex.o testComplex.o -o testComplex

testComplex.o: testComplex.cpp Complex.h
				g++ -c testComplex.cpp

Complex.o: Complex.cpp Complex.h
			g++ -c Complex.cpp

