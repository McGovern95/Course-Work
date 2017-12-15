all:	lab3

lab3:	textfunctions.o	lab3.o
		gcc textfunctions.o	lab3.o	-o	lab3

lab3.o:	lab3.c	textfunctions.h
		gcc	-c	lab3.c

textfunctions.o:	textfunctions.c	textfunctions.h
					gcc	-c	textfunctions.c

clean: 
		rm	-rf	*.o