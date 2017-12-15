//header comments 
#include "functions4a.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    /*
     * Function which copies the lowercase letters from original to lower
	 * and vise-versa 
	 *
	 */	
	void splitAlpha(const char *original, char *lower, char *upper){
         //variable declerations 
        
        int i;
        int size = strlen(original);
         //for loop, goes through the string
        for(i = 0; i <= size; i++){
        		//sets all lowercase letters equal to *lower and increments lower to next character
        	 if(original[i] >= 'a' && original[i] <= 'z'){
              		*lower = original[i];
              	     lower++;
             } //sets all highercase letters equal to *higher and increments higher to next character
                else if(original[i] >= 'A' && original[i] <= 'Z'){
              		   *upper = original[i];
              		    upper++;
                }
           //puts null character at end of *upper and *lower
          *upper = '\0';
          *lower = '\0';
        }//end for
        
	}//end splitAlpha 

	/*
	 * Function which prints all subsequence characters that occur
	 * prints a \n at end of sequence
	 *
	 */
	void printSequences(const char *text){
     	//variable declerations 
	 	int i;
	
        //for loop, goes through the string 
	 	for(i = 0; text[i] != '\0'; i++){

    if(text[i] + 1 != text[i + 1])
      printf("\n");
     else
      printf("%c", text[i]);
                

        }//end for

	}//end printSequences