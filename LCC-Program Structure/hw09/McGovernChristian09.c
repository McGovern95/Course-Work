/*
 * Program which calculates compund interest. 
 *
 * @author: Christian McGovern
 * @assignment: ICS 212 #9
 * @date: 9/23/15
 */
 
 
#include <stdio.h>
#include "getdouble.h"

    int main (void) {
    
    double principle = 0.0;
    double annualRate = 0.0;
    double compPerYear = 0.0;
    double totalYears = 0.0;
    double eNum = 0.0;
    
    
    printf("This program will see how much your money grows with compuund interest!\n");
 
   
    printf("Please enter the principle: ");
    principle = getdouble();
    
    printf("Please enter the annual rate (In decimal format): ");
    annualRate = getdouble();
    
    printf("Please enter the rate at which it compounds (by months): ");
    compPerYear = getdouble();
    
    printf("Please enter the total time in years: ");
    totalYears = getdouble();
    
    double totalAmount = principle * pow((1 + (annualRate/compPerYear)), compPerYear * totalYears );//pow();
     
    printf("Your future value is: %d\n", (int)fabs(floor(ceil(totalAmount))) );//fabs();floor();ceil();
   
    printf("Bonus! Enter a number to find its e: ");
    
    eNum = getdouble();
    
    printf("%f\n", exp(eNum));//exp();
  
    return 0;
    
    } // end of main