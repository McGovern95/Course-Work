/*
 * Program which displays 5 different examples of recursion 
 * @author: Christian McGovern
 * @assignment: ICS 212 #11
 * @date: 10/5/15
 */

#include <stdio.h>
#include "getdouble.h"


void count(int n1, int n2);
int sum(int n1, int n2);
int product(int n1, int n2);
int power(int n1, int n2);
int gcd(int n1, int n2);

int main() {

  int n1;
  int n2;

 printf("Enter two positve integers, seperated by a space, the first smaller than the second: \n");
 
  n1 = (int)getdouble();
  n2 = (int)getdouble();
  
  if(n1 < 0 || n2 <0){
     printf("Please enter only positive numbers\n");
  }
   else if(n1 > n2){ 
     printf("%d is bigger than %d\n", n1,n2); 
   }
    else {
 printf("Counting from %d to %d = ", n1, n2);
 count(n1, n2);//count
 printf("\nSum of %d and %d = %d\n", n1, n2, sum(n1, n2));//sum
 printf("The product of %d and %d = %d\n", n1, n2, product(n1,n2));//product
 printf("%d to the power of %d = %d\n", n1, n2, power(n1, n2));//power
 printf("GCD of %d and %d = %d\n", n1, n2, gcd(n1, n2));//gcd

 
 }
 return 0;

}//end of main

void count(int n1, int n2) {
   printf(" %d ", n1); 
  if(n2 != 0 && n1 < n2 ){
     count(n1 + 1, n2);
  }
    else{
      return;
    }

}//end of count*/

int sum(int n1, int n2){
  if(n1 != 0) {
     return sum(n2, n1 - 1) + 1;
  }
 else {
    return n2;
 }
   
}//end of sum */

int product(int n1, int n2){
  
  if(n2 != 0){
     return (n1 + product(n1, n2 -1));
  }
   else{
     return n2;
   }

}//end of product

int power(int n1, int n2){
  if(n2 != 1){
     return (n1 * power(n1, n2 - 1));
  }
   else {
     return n1;
   }

}//end of power

int gcd(int n1, int n2){
  if (n2 != 0){
      return gcd(n2, n1 % n2);
   }
   else{
        return n1;  
   }

}//end of GCD 