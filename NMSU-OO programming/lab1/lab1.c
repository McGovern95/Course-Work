//CS 271
//Program Name: lab1
//Author: Christian McGovern
//Date: 1/24/17
//This program will determine the average between 4 exam scores which is entered, displaying the letter grade as well.

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

  int main (void){
    
    //variables
    double exam1, exam2, exam3, exam4, average;
    char letterGrade;
  
    //while loop
    while(1){
      printf("Enter the 1st exam score: \n");
      scanf("%lf", &exam1);
      printf("Enter the 2nd exam score: \n");
      scanf("%lf", &exam2);
      printf("Enter the 3rd exam score: \n");
      scanf("%lf", &exam3); 
      printf("Enter the 4th exam score: \n"); 
      scanf("%lf", &exam4); 
      average = (exam1 + exam2 + exam3 + exam4)/ 4; 
      
      //checks to see if the sentinel is inputted
      if(exam1 == -1 && exam2 == 0 && exam3 == 0 && exam4 == 0 ){
	return;
      }
      //Displays the Exam scores and Average 
      printf("Exam Scores: %.0f, %.0f, %.0f, %.0f\n", exam1, exam2, exam3, exam4);
      printf("Average: %.2f\n", average);
      
      //calculates the letter grade from average 
      if(0 <= average && average < 60){
	letterGrade = 'F';
      }
      else if(60 <= average && average < 70){
	letterGrade = 'D'; 
      }
      else if(70 <= average && average < 80){
	letterGrade = 'C'; 
      }
      else if(80 <= average && average < 90){
	letterGrade = 'B'; 
      }
      else if(90 <= average && average < 100){
	letterGrade = 'A'; 
      }
      
      printf("Letter Grade: %c\n", letterGrade);
      
   }//end of while
    
    
    
    
    
  }//end of main

