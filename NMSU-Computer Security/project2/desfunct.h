#ifndef DESFUNCT_H
#define DESFUNCT_H

typedef struct {
	unsigned char k[8];
	unsigned char c[4];
	unsigned char d[4];
} set_key;

void keyGenerator(unsigned char* key);
void ivGenerator(char* iv);
void subkeyGenerator(char* main_key, set_key* setkeys);
void desFunction( char* message, char* processed, set_key* setkeys, int mode);

#endif