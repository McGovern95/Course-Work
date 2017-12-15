program: McGovernChristian11.o getdouble.o
	 gcc McGovernChristian11.o getdouble.o -o program -lm

McGovernChristian11.o: McGovernChristian11.c getdouble.h
		       gcc -c McGovernChristian11.c

getdouble.o: getdouble.c getdouble.h
	     gcc -c getdouble.c
