#ifndef DESFUNCT_H
#define DESFUNCT_H

//struct used for temporary arrays for subkey generation
typedef struct subKeyType{
	unsigned char keyTemp[8];
	unsigned char t2[4];
	unsigned char t3[4];
} subKey;

void generator(unsigned char*, unsigned char*);
void subkeyGenerator(subKey*, unsigned char*);
void desFunction(subKey*, unsigned char*, unsigned char*, int);

#endif
