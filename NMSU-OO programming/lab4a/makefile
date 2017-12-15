all: 	lab4a

lab4a: functions4a.o lab4a.o
		gcc functions4a.o lab4a.o -o lab4a

lab4a.o: lab4a.c functions4a.h
		gcc -c lab4a.c

functions4a.o:	functions4a.c functions4a.h
				gcc -c functions4a.c 