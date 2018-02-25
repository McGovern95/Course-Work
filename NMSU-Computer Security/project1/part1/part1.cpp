//CS 478
//Program Name: part1
//Author: Christian McGovern
//Date: 2/25/18
//This program displays letter frequency of a cipher and compares it
//with a dictionary


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "cipherfunct.h"

int main(){

	if(!computeFrequency())
		printf("Cipher key: \n\n");
		printf("%s\n", cipher);

    while(true){
	sortByFreq();
	if(!manualDecrypt())
		printf("%s\n", plain);

	//permute();
	
	printFrequency();

	dictionarycompute();
	}//end while

}//end main


