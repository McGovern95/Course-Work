//CS 271
//Program Name: lab3
//Author: Christian McGovern
//Date: 2/25/17
//This program demonstrates an understanding with manipulating strings and pointers.  
#include <stdio.h>
#include "textfunctions.h"



int main(void){

    char line[80];
    int count;

    FILE *cfPtr;

    if((cfPtr = fopen("lines.dat", "r")) == NULL) {

        puts("File could not be opened\n");
    }
     else{
            /*
               directions from lab3.pdf
               1. input the string
               2. print the words in the string
               3. remove the punctuation 
               4. print the words 
               5. sort the string 
               6. print the blocks in the string 
            */

        //1. 
     	fgets(line, 80, cfPtr);

     	while(!feof(cfPtr)){

            //2.
            printf("Line Read: %s\n\n", line);
            //my code
            //3.
            removePunctuation(line);
            //4.
            wordPrint(line);
            //5. 
            stringSort(line);
            //6. 
            blockPrint(line);
            printf("\n");
            //end my code
          

     		fgets(line, 80, cfPtr);
       

     	}//end while
      
     	fclose(cfPtr);
     }//end else
     

}//end main