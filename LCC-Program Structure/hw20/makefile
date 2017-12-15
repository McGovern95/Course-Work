program: McGovernChristian20.o getdouble.o stringinput.o
	 gcc McGovernChristian20.o getdouble.o stringinput.o -o program

getdouble.o: getdouble.c getdouble.h
	gcc -c getdouble.c

stringinput.o: stringinput.c stringinput.h
	gcc -c stringinput.c

McGovernChristian20.o: McGovernChristian20.c getdouble.h stringinput.h student.h
	gcc -c McGovernChristian20.c 