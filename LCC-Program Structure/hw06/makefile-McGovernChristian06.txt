program: McGovernChristian06.o getdouble.o
	 gcc McGovernChristian06.o getdouble.o -o program -lm

McGovernChristian06.o: McGovernChristian06.c getdouble.h 
		       gcc -c McGovernChristian06.c

getdouble.o: getdouble.c getdouble.h
	     gcc -c getdouble.c 
