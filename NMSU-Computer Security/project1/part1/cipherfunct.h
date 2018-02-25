/*header file*/
#ifndef CIPHERFUNCT_H
#define CIPHERFUNCT_H

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern int freq[26][3];
extern int pos[26];
extern char cipher[1000], plain[1000], key[26];

void stringUpr(char *);
int dictCompute();
int computeFreq();
int printFreq();
int Decrypt();
int sortFreq();
int permute();

#endif
