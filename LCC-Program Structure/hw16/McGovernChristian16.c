/*
 * Calculator program which demonstrates commandline
 * @author: Christian McGovern
 * @assignment: ICS 212 #16
 * @date: 10/21/15
 */

#include <stdio.h>
#define SIZE 5

//prototypes 
int add(int,int);
int sub(int,int);
int mul(int,int);
int div(int,int);

int main(int argc, char *argv[]) {

 //initalize variables
 int num1;
 int num2;
 int index;
 int results;
 
 //ERROR CHECKING
 if(argc < 4){
      printf("Enter at least 4 arguments on the commandline\n");
      exit(1); //quit the program
   } 
 if(argv[1][0] < '0' || argv[1][0] > '9'){
   printf("1st arguement is not a number from 0-9\n");
   exit(1);
 }//1st argument error checking
  if(argv[3][0] < '0' || argv[3][0] > '9'){
   printf("4th arguement is not a number from 0-9\n");
   exit(1);
 }//4th arguement error checking
 if(argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != '.' && argv[2][0] != '/'){
   printf("Please enter the operator '+' or '-' or '.' or '/' for the 3rd arguement please");
   exit(1);
 }//operator error checking
   
  
  //conversion of operators and integers 
  num1 = argv[1][0] - '0';
  num2 = argv[3][0] - '0';
  index = argv[2][0] - '+';
 
  //declared a array of functions 
  int (*array[SIZE])(int,int) = {add, NULL, sub, mul, div};
  
 //output
  results = array[index](num1, num2);
  printf("%i\n", results);

 return 0;
}
//function definitions

int add(int x, int y){
   return x + y;
}//end of add

int sub(int x, int y){
   return x - y;
}//end of sub

int mul(int x, int y){
   return x * y;
}//end of mul

int div(int x, int y){
   return x / y;
}//end of div