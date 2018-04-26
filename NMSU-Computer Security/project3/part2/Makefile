all: part2

part2: part2.o
	gcc part2.o -o part2
	
part2.o: part2.c part2.h
	gcc part2.c -o part2 -I/usr/local/ssl/include -L/usr/local/ssllib -lssl -lcrypto
	
clean:
	rm -rf *o part2
