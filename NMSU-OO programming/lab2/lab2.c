//CS 271
//Program Name: lab2
//Author: Christian McGovern
//Date: 2/14/17
//This program demonstrates proficiency in writing functions and arrays using 5 functions 
#include "lab2functions.h"
#include <stdio.h>

	int main (void){

         //variables and array declerations 
        int SIZE = 10;
		int i_array[] =       {2, 444, 5, 4, 421, 2, 2, 112, 3, 20};
		int secondi_array[] = {1, 444, 4, 4, 488, 2, 3, 456, 3, 20};
		char c_array[] = {'A', 'b', 'c', 'd', 'e', 'F', 'g', 'h', 'i', 'j'};
         //function calls
         printArray(SIZE, i_array );
	     printCharArray(SIZE, c_array);
	     arrayMin(SIZE, i_array);
	     countLetters(SIZE, c_array);
	     numMatches(SIZE, i_array, secondi_array);



	}//end of main