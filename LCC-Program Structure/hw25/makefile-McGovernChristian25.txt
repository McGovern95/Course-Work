program: McGovernChristian25.o
	 g++ McGovernChristian25.o -o program

McGovernChristian25.o: McGovernChristian25.cpp
		       g++ -c McGovernChristian25.cpp
