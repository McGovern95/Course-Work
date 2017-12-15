/*
Writes to a file with 20 fixed-length records
*/
#include <stdio.h>   
#include "student.h"
#include "getdouble.h"
#include "stringinput.h"

void printStudent(Student);
  
int main(){   
   Student studentX = {-1, "", "", 0, 0.0 };      
   FILE *filePointer = NULL;    
   char *fileName = "students.txt";
   int fileClosed = 0;  
   int seekError = 0;
   int writeError = 0;
  
   /*
   open a connection to a file
   note: using "w" will overwrite the data
   "r+" = update an existing file for reading and writing
   */ 
   filePointer = fopen(fileName,"r+");
  //if error, filePointer is NULL 
   if(filePointer == NULL){
      printf("File \"%s\" could not be opened. \n", fileName); 
      exit(1); //end the program
   }//end of else   
   else {       
      printf("Enter student number (0 to %d), or %d to quit: \n", MAX_RECORDS-1, MAX_RECORDS); 
      studentX.number = getdouble();    
      while(studentX.number >= 0 && studentX.number < MAX_RECORDS){
      //get user input
         printf("Enter first name, last name, age, and gpa separated by spaces: \n");         
         getstring(studentX.first, MAX_STRING);
         getstring(studentX.last, MAX_STRING);
         studentX.age = getdouble();
         studentX.gpa = getdouble();
      //find record to update in file
         seekError = fseek(filePointer,(studentX.number)*sizeof(Student), SEEK_SET);
         if(0==seekError){
            printf("Record #%d was correctly located in file  \"%s\". \n", studentX.number, fileName);
         }
         else{
            printf("Record #%d was NOT correctly located in file  \"%s\". \n", studentX.number, fileName);
         }
         
         //write new record to file
         writeError = fwrite(&studentX,sizeof(Student),1,filePointer);
         if(1 == writeError){
            printf("Record #%d was correctly written to file  \"%s\". \n", studentX.number, fileName);
         }
         else{
            printf("Record #%d was NOT correctly written to file  \"%s\". \n", studentX.number, fileName);
         }
         //output record
         printStudent(studentX);
         //prompt user again      
         printf("Enter student number (0 to %d), or %d to quit: \n", MAX_RECORDS-1, MAX_RECORDS);
         studentX.number = getdouble();     
      }      
    //close the file connection
      fileClosed = fclose(filePointer);
      if(0 == fileClosed){
         printf("File connection to \"%s\" closed successfully.\n", fileName);
      }//end of if
      else{
         printf("File connection to \"%s\" did NOT close successfully.\n", fileName);
      }//end of else    
   }//end of else 
}//end of main

 //display Student structure
void printStudent(Student studentX){
   printf("%6d  %9s  %8s  %3d  %3.1f  \n", 
               studentX.number, 
               studentX.first, 
               studentX.last, 
               studentX.age, 
               studentX.gpa);
}

