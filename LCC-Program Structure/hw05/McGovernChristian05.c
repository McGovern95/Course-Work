/* 
* Program which asks a user to enter two letters and two numbers
* @author: Christian McGovern
* @assignment: ICS 212 Assignment #5
* @date: 8/28/2015
*
*/

#include <stdio.h>

#include "getdouble.h" 

   int main (void) {

     /* variables to initialize getchar(); and getdouble();  */

     char letter = 'A';
     char letter2 = 'B';
     

     double number = 0.0;
     double number2 = 1.1;

       
     printf("Please enter a letter: ");
     letter = getchar();     
     printf("The 1st letter is: '%c'\n", letter);
    
     getchar(); /* gets the \n char off */

     printf("Please enter a second letter: ");
     letter2 = getchar();
     printf("The 2nd letter is: '%c'\n", letter2);
 
     getchar(); /* gets the \n char off*/
     
     printf("Please enter a number: ");
     number = getdouble();
     printf("The 1st number is: %f\n", number);

     printf("Please enter a second number: ");
     number2 = getdouble();
     printf("The 2nd number is; %f\n", number2); 

     return 0; 

   } /* end of main */
