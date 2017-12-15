/* 
 * Program demosnstrating pointers
 * @author: Christian McGovern
 * @assignment: ICS 212 #14
 * @date: 10/14/15
 */

#include <stdio.h>

int main(){

  //initialize variables
  int var1 = 1;
  char var2 = 'b';
  double var3 = 3.3;
  
  //initialize pointers
  int *pointerint = NULL;
  char *pointerchar = NULL;
  double *pointerdouble = NULL;
  
  //assigning address to pointer
  pointerint = &var1;
  pointerchar = &var2;
  pointerdouble = &var3;
   
  //addresses and values 
  printf("address: pointerint = 0x%p\nvalue: var1 = %i\n", pointerint, *pointerint);
  printf("address: pointerchar = 0x%p\nvalue: var2 = %c\n", pointerchar, *pointerchar);
  printf("address: pointerdouble = 0x%p\nvalue: var3 = %f\n", pointerdouble, *pointerdouble);
  
  //add 3 to value using dereference
  *pointerint = *pointerint + 3;
  *pointerchar = *pointerchar + 3;
  *pointerdouble = *pointerdouble + 3;
 
  //outputting new value 
  printf("var1 + 3 = %d\n", var1);
  printf("var2 + 3 = %c\n", var2);
  printf("var3 + 3 = %f\n", var3);
  
  return 0; 
}//end of main

