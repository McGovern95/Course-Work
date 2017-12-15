all:	lab2

lab2:	lab2functions.o	lab2.o
	gcc lab2functions.o	lab2.o	-o	lab2

lab2.o:	lab2.c	lab2functions.h
	gcc -c	lab2.c

lab2functions.o:	lab2functions.c	lab2functions.h
	gcc -c	lab2functions.c

clean:
	rm	-rf	*.o