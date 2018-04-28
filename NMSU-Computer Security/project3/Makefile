all: project3

project3: part2 part3

part2: part2.c part2.h
	gcc part2.c -o part2 -I/usr/local/ssl/include -L/usr/local/ssllib -lssl -lcrypto

part3: part3.c part3.h
	gcc part3.c -o part3 -I/usr/local/ssl/include -L/usr/local/ssllib -lssl -lcrypto

clean:
	rm -rf *o part2 part3
