program: McGovernChristian15.o
	 gcc McGovernChristian15.o -o program

McGovernChristian15.o: McGovernChristian15.c
		       gcc -c McGovernChristian15.c
