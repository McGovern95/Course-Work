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

    printf("This program takes cipertext.txt, accepts a key, and sorts it\n\
by the most frequent letters. If the correct key is given\n(from most to least\
frequent letters) then the correct plain text will be given\n\n");

	if(!computeFreq())
		printf("Cipher key: \n\n");
		printf("%s\n", cipher);

    while(1){
	sortFreq();
	if(!decrypt())
		printf("%s\n", plain);

	//permute();//not working
	
	printFreq();

	dictCompute();
	}//end while

}//end main


