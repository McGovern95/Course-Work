//header comments
#include "lab2functions.h"
#include <stdio.h>
    
	int printArray(int SIZE, int i_array[]){
	  //variables 
	  int i;
	  
	  printf("First function printArray():\n");
	  
	  for(i = 0; i < SIZE; i++){
	    int max_width = 5;
	    
	    printf("%*d", max_width, i_array[i]);
	   
	  
	  }//end of for
	  printf("\n"); 
	}//end of printArray()
	
	char printCharArray(int SIZE,char c_array[]){
	  //variables 
	  int i; 
	  
	  printf("Second function printCharArray():\n");
	  
	  for(i = 0; i < SIZE; i++){
	    
	    printf("%c ", c_array[i]);
	    
	  }//end of for
	  printf("\n");
	}//end of printCharArray()
	
	int arrayMin(int SIZE, int i_array[]){

		int i;
		int smallest = i_array[0];
		printf("Third Function arrayMin():\n");

		for (i = 0; i < sizeof(i_array)/sizeof(i_array[0]); ++i){
			if (i_array[i] < smallest){
				smallest = i_array[i];	
			}//end of if

         }//end of for

		printf("%d", smallest);

	  printf("\n");
	}//end of ArrayMin()
	
	char countLetters(int SIZE, char c_array[SIZE]){
 	  //variables 
      int count;
      int i;
      printf("Fourth Function countLetters(): \n");

       for(i = 0; i < SIZE; i++){

	       if (c_array[i] >= 'a' && c_array[i] <= 'z') 
                count++;
    
    		 else if (c_array[i] >= 'A' && c_array[i] <= 'Z') 
        			   count++; 
    

   }//end of for

	     printf("%d",count - 2);//for loop adds 2 to count for some reason 

	  printf("\n");
	}//end of countLetters()  
	
	int numMatches(int SIZE, int i_array[], int secondi_array[]){

		int i;
		int count;
		printf("Fifth Function numMatches(): \n");
		for(i = 0; i < SIZE; i++){

			if(i_array[i] == secondi_array[i])
				count++;
			
		}//end of for

		printf("%d",count - SIZE);//subtract SIZE because That gives the correct amount,
		                        //not sure why, but depending on SIZE, you'll subtract
		                        //by SIZE on count to get the correct number
		printf("\n");
	  
	  
	}//end of numMatches()