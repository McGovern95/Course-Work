/*
   program which demonstrates file processing 
*/

#include <stdio.h>   
#include <stdlib.h>
#include "student.h"
#include "getdouble.h"
#include "stringinput.h"

void printStudent(Student);
void mainMenu();
void addRecord();
void editRecord();
void fileRead();
  
int main(){
	
	mainMenu();
   
}//end of main

 //display Student structure
void printStudent(Student studentX){
   printf("%6d  %9s  %8s  %3d  %3.1f  \n", 
               studentX.number, 
               studentX.first,  
               studentX.last, 
               studentX.age, 
               studentX.gpa);
}//end of printStudent();

void mainMenu(){
	char selection = NULL;
	char bufferClear = NULL;
	printf("Would you like to add(a) a record, edit(e) a record, or quit(q)? ");
	selection = getchar();
	bufferClear = getchar();
	if(selection == 'a'){
		//add a record
		addRecord();
		mainMenu();
	}
	else if(selection == 'e'){
		//edit a record
		editRecord();
		mainMenu();
	}
	else if(selection == 'q'){
		//quit
		exit(1);
	}
	else{
		printf("ERROR: %c is not a valid choice.\n",getchar());
	}
}

void addRecord(){
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
      printf("Enter student number (0 to %d), or %d to return to main menu: \n", MAX_RECORDS-1, MAX_RECORDS); 
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
            printf("Record #%d was not correctly located in file  \"%s\". \n", studentX.number, fileName);
         }
         
         //write new record to file
         writeError = fwrite(&studentX,sizeof(Student),1,filePointer);
         if(1 == writeError){
            printf("Record #%d was correctly written to file  \"%s\". \n", studentX.number, fileName);
         }
         else{
            printf("Record #%d was not correctly written to file  \"%s\". \n", studentX.number, fileName);
         }
         //output record
         printStudent(studentX);
         //prompt user again      
         printf("Enter student number (0 to %d), or %d to return to main menu: \n", MAX_RECORDS-1, MAX_RECORDS);
         studentX.number = getdouble();     
      }      
    //close the file connection
      fileClosed = fclose(filePointer);
      if(0 == fileClosed){
         printf("File connection to \"%s\" closed successfully.\n", fileName);
      }//end of if
      else{
         printf("File connection to \"%s\" did not close successfully.\n", fileName);
      }//end of else    
   }//end of else	
}//end of addRecord();

void editRecord(){
	int i = 0; 
	Student studentX = {-1, "", "", 0, 0.0 };      
	FILE *filePointer = NULL;    
	char *fileName = "students.txt";
	int fileClosed = 0;  
	int seekError = 0;
	int readError = 0; 
	int writeError = 0;
	
	int editNum = -1;
	char selection = 'z';
	char clearBuffer = 'z';
	char found = 'n';
  
	fileRead();
  
	/*
	open a connection to a file
	"w" will overwrite the data
	"r+" will update an existing file for reading and writing
	*/ 
	filePointer = fopen(fileName,"r+");
	//if error, filePointer is NULL 
	if(filePointer == NULL){
		printf("File \"%s\" could not be opened. \n", fileName); 
		exit(1); //end the program
	}//end of else 		
	else { 
		printf("Enter the record number you wish to edit or %d to return to main menu: ",MAX_RECORDS);
		editNum = getdouble();
		if(editNum < 0){
			printf("ERROR: No negative numbered records exist.\n");
			editRecord();
		}
		else if(editNum == MAX_RECORDS){
			mainMenu();
		}
		else{
			while(0 == feof(filePointer)){
			//read from file
				readError = fread(&studentX,sizeof(Student),1,filePointer);
				if(1 == readError){
					//printf("Record #%d was correctly read from file  \"%s\". \n", i, fileName);
					//studentArray[i] = studentX;
					if(studentX.number == editNum){
						printf("Student Number: %d\n", studentX.number);
						found = 'y';
						break;
					}
					//printStudent(studentArray[i]);
				}
				else{
				//printf("Record #%d was NOT correctly read from file  \"%s\". \n", i, fileName);
				}
				i++;
			}//end of while loop
			if(found == 'n'){
				printf("ERROR: Record #%d does not exist.\n", editNum);
				editRecord();
			}
			else if(found == 'y'){
				printf("You selected record #%d:\n",editNum);
				printStudent(studentX);
				printf("Do you wish to edit first name (f), last name (l), age (a), or gpa (g)?");
				
				selection = getchar();
				clearBuffer = getchar();
				switch(selection){
					case 'f':
						printf("Enter new first name: ");
						getstring(studentX.first, MAX_STRING);
						break;
					case 'l':
						printf("Enter new last name: ");
						getstring(studentX.last, MAX_STRING);
						break;
					case 'a':
						printf("Enter new age: ");
						studentX.age = getdouble();
						break;
					case 'g':
						printf("Enter new gpa: ");
						studentX.gpa = getdouble();
						break;
					default:
						printf("ERROR: %c is not a valid option.\n",selection);
				}//end of case statements
				
				seekError = fseek(filePointer,(studentX.number)*sizeof(Student), SEEK_SET);

				writeError = fwrite(&studentX,sizeof(Student),1,filePointer);

				//close the file connection
				fileClosed = fclose(filePointer);
				if(0 == fileClosed){
					printf("File connection to \"%s\" closed successfully.\n", fileName);
				}//end of if
				else{
					printf("File connection to \"%s\" did NOT close successfully.\n", fileName);
				}//end of else
				printf("\n");
				editRecord();
			}
		}
	}
}//end of editRecord()

void fileRead(){
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
      while(0 == feof(filePointer) || i < MAX_RECORDS-1){
      //read from file
         readError = fread(&studentX,sizeof(Student),1,filePointer);
         if(1 == readError){
            //printf("Record #%d was correctly read from file  \"%s\". \n", i, fileName);
            studentArray[i] = studentX;   
            //printStudent(studentArray[i]);
         }
         else{
            //printf("Record #%d was NOT correctly read from file  \"%s\". \n", i, fileName);
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
	  printf("\n");
      
   }//end of else
}//end of fileRead();