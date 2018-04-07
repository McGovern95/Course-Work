#ifndef DESFUNCT_H
#define DESFUNCT_H

typedef struct {
	unsigned char k[8];
	unsigned char c[4];
	unsigned char d[4];
} keySet;

void keyGenerator(unsigned char*);
void ivGenerator(unsigned char*);
void subkeyGenerator(unsigned char* , keySet* );
void desFunction( unsigned char*, unsigned char*, keySet*, int);

#endif
