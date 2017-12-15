program: McGovernChristian16.o
	 gcc McGovernChristian16.o -o program

McGovernChristian16.o: McGovernChristian16.c
		       gcc -c McGovernChristian16.c
