
#ifndef CIPHERFUNCT_H
#define CIPHERFUNCT_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern int freq[26][3];
extern int pos[26];
extern char cipher[1000], plain[1000], key[27];

void stringUpr(char *);
int dictionarycompute();
int computeFrequency();
int printFrequency();
int manualDecrypt();
int sortByFreq();
int permute();

#endif
