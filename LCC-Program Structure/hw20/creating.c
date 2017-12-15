/*
  Creating a file for 20 fixed-length records
*/
#include <stdio.h>   
#include "student.h"

int main(){       
   int i = 0;      
   Student blank = {-1, "", "", 0, 0.0 };      
   FILE *filePointer = NULL;    
   char *fileName = "students.txt";
   int fileClosed = 0; 
   int writeError = 0;
  
   printf("sizeof(Student)=%d\n", sizeof(Student));
  
  //open a connection to a file
   filePointer = fopen(fileName,"w");
  //if error, filePointer is NULL 
   if(filePointer == NULL){
      printf("File \"%s\" could not be opened. \n", fileName); 
      exit(1); //end the program
   }//end of else          
   else {                
      for(i=0;i<MAX_RECORDS;i++){
      /*
      Make room to add records to a file.
      Variable "blank": is written to the file.
      sizeof(): calculates the number of bytes in the struct.
      Integer 1: means we are writing just one record to the file.
      filePointer: is the file we are writing to.
      */
         writeError = fwrite(&blank,sizeof(Student),1,filePointer); 
         if(1 == writeError){
            printf("Record #%d was correctly written to file  \"%s\". \n", i, fileName);
         }
         else{
            printf("Record #%d was NOT correctly written to file  \"%s\". \n", i, fileName);
         }
      }//end of for loop
    //close the file connection
      fileClosed = fclose(filePointer);
      if(0 == fileClosed){
         printf("File connection to \"%s\" closed successfully.\n", fileName);
      }//end of if
      else{
         printf("File connection to \"%s\" did NOT close successfully.\n", fileName);
      }//end of else    
   }//end of else         
   return 0;
}



