//header comments 
#include "textfunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

  void removePunctuation(char *line){
	 //variable declerations
     char *index1 = line, *index2 = line;

     while (*index1 != '\0'){

     	 if(ispunct(*index1)){
         	//does nothing if there is punctuation
       	 	//increments to next character 
         	index1++;
         }
      	  else if(index1 == index2){
          		//increments both characters when same, and doesnt copy to line 
          		index1++;
         	    index2++;
          }
       	   else
    	    	//copies the character from second index and increments them both on line
           	   *index2++ = *index1++;
       		
     }//end while
   
        *index2 = '\0';//sets the second index to null, will output last couple of 
                       // characters again if not set to null
    
	}//end removePunctuation();

  void stringSort(char *line){
         //variable declerations
     int i, j;
     char temp;
     char *index = line;
     int size = strlen(index);
     int numPasses = size - 1;
          //bubble sorting loop
     for(i = 1; i <= numPasses; i++){//first pass through

   		  for(j = 0; j < size - i; j++){

     			if(index[j] > index[j + 1]){

        			 temp = index[j];
         			 index[j] = index[j + 1];
        			 index[j + 1] = temp;

       		    }//end if
          	 	
      	   }//end second for

     }//end first for

	}//end stringSort();

  void blockPrint(char *line){
		//variable declerations
     int i;
     char *index = line;
	   int size = strlen(index);

	 for(i = 0; i <= size - 1; i++){

 	 	if(index[i] != index[i + 1])
 			printf("%c \n",index[i]);
	 	 else
			printf("%c ", index[i]);
				     		
	
		}//end for

	}//end blockPrint();

  void wordPrint(char *line){
		 //variable declerations
	 int i;
	 char *index = line;

	 for(i = 0; index[i] != '\0'; i++){

		 if(index[i] == ' ')
		    printf("\n");
	 	  else 
         	printf("%c", index[i]);

	 }//end of for

	}//end wordPrint();