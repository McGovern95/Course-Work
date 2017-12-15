//CS 271
//Program Name: lab4a
//Author: Christian McGovern
//Date: 3/09/17
//This program demonstrates an understanding with manipulating strings and pointers.  
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

   int main(void){
	
        //all pointer variables given 80 spots in an array 
       const char original[80] = "The symbol for Intel is INTC.";
       char lower[80], upper[80];   
       splitAlpha(original, lower, upper);
       printf("the original string is: %s\n", original);
       printf("the lower case letters of this string is: %s\n", lower);
       printf("the upper case letters of this string is: %s\n", upper);
       //printSequences testing 
       const char text[80] = "abk123@XY";
       printf("the original sequence of strings is: %s\n", text);
       printf("new string is: \n");
       printSequences(text);


    }//end of main 