program: McGovernChristian08.o 
	 gcc McGovernChristian08.o -o program

McGovernChristian08.o: McGovernChristian08.c
		       gcc -c McGovernChristian08.c
