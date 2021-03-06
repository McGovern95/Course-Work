/*
 * Program which will calculate your age in days
 * @author: Christian McGovern
 * @assignment: ICS 212 Assignment #6
 * @date; 8/30/2015
 *
 */

#include <stdio.h>

#include "getdouble.h"
#define Title "This program will calculate your age in days."// symbolic constant

     int main (void) {
       //variables to initilaize getdouble();

       double month = 0.0;
       double day = 1.1;
       double year = 3.3;

       puts(Title);// puts
       //month print
       printf("Enter the month you were born: ");
       month = getdouble();
       //day print
       printf("Enter the day you were born: ");
       day = getdouble();
       //year print   
       printf("Enter the year you were born: ");
       year = getdouble();
    
      printf("Today's date is: 9/14/2015 \n");
     
      int currentdate = (365.25 * 2015) + (365.25/12 * 9)+ 14;//double
  
      int userage = (365.25 * year) + (365.25/12 * month) + day;
 
      int userdays = currentdate - userage;  //int
    
       //bunch of stuff above 
      printf("Your age in days is: %d,%.3d\n", userdays/1000, userdays%1000);


       return 0;
}
