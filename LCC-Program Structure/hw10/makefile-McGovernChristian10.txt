program: McGovernChristian10.o
	 gcc McGovernChristian10.o -o program -lm

McGovernChristian10.o: McGovernChristian10.c
		       gcc -c McGovernChristian10.c
