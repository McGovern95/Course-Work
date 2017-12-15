/*
Reads from a file with 20 fixed-length records
*/
#include <stdio.h>   
#include "student.h"
#include "getdouble.h"
#include "stringinput.h"

void printStudent(Student);
  
int main(){   
   int i = 0;      
   Student studentX = {-1, "", "", 0, 0.0 };
   Student studentArray[MAX_RECORDS] = {-1, "", "", 0, 0.0 };
   FILE *filePointer = NULL;    
   char *fileName = "students.txt";
   int fileClosed = 0; 
   int readError = 0; 
  
   /*
   open a connection to a file
   */ 
   filePointer = fopen(fileName,"r");
  //if error, filePointer is NULL 
   if(filePointer == NULL){
      printf("File \"%s\" could not be opened. \n", fileName); 
      exit(1); //end the program
   }//end of else   
   else {       
      while(0 == feof(filePointer)){
      //read from file
         readError = fread(&studentX,sizeof(Student),1,filePointer);
         if(1 == readError){
            printf("Record #%d was correctly read from file  \"%s\". \n", i, fileName);
            studentArray[i] = studentX;   
            printStudent(studentArray[i]);
         }
         else{
            printf("Record #%d was NOT correctly read from file  \"%s\". \n", i, fileName);
         }
         i++;
      }//end of while loop
    //close the file connection
      fileClosed = fclose(filePointer);
      if(0 == fileClosed){
         printf("File connection to \"%s\" closed successfully.\n", fileName);
      }//end of if
      else{
         printf("File connection to \"%s\" did NOT close successfully.\n", fileName);
      }//end of else    
      
      //display all records
      printf("\nNumber  FirstName  LastName  Age  GPA  \n"); 
      printf("------  ---------  --------  ---  ---  \n");
      for(i=0;i<MAX_RECORDS;i++){
         if(-1 != studentArray[i].number){  
            printStudent(studentArray[i]); 
         }
      }
      
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

