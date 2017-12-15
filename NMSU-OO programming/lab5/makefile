all: Lab5Test

Lab5Test: Concert.o Lab5Test.o Time.o
			g++ Concert.o Lab5Test.o Time.o -o Lab5Test 

Lab5Test.o: Lab5Test.cpp Concert.h Time.h
			g++ -c Lab5Test.cpp

Concert.o: Concert.cpp Concert.h Time.h
			g++ -c Concert.cpp

Time.o: Time.cpp Time.h
		g++ -c Time.cpp