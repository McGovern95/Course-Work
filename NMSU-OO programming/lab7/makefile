all: TimeTest

TimeTest: Time.o TimeTest.o PreciseTime.o
			g++ Time.o TimeTest.o PreciseTime.o -o TimeTest

TimeTest.o: TimeTest.cpp Time.cpp PreciseTime.cpp
			g++ -c TimeTest.cpp

Time.o: Time.cpp Time.h
			g++ -c Time.cpp

PreciseTime.o: PreciseTime.cpp PreciseTime.h
				g++ -c PreciseTime.cpp
