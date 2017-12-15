/*
 * Program demonstrating pointers and arrays
 * @author: Christian McGovern
 * @assignment: ICS 212 #15
 * @date: 10/19/2015
 */

#include <stdio.h>
#define SIZE 5

int main(){

   //declare and initilaize variables 
   int array[] = {10,20,30,40,50};
   int *pointer = NULL;
   int i = 0;
   //assign the array's address to the pointer 
   pointer = array;
   

   //the array address of each element
   printf("Array addresses: \n");
   for(i = SIZE - 1;i >= 0;i--){
      printf("array[%i] = 0x%p\n",i ,&array[i]);
   } 
   printf("\n");
   printf("5th element 4 ways: \n");
   //subscript notation 
   printf("subscript notation: array[4] = %i\n", array[4]);
   //pointer/offset notation
   printf("pointer/offset notation: *(array + 4) = %i\n", *(array + 4));
   //subscript notation using pointer
   printf("subscript notation using pointer: pointer[4] = %i\n", pointer[4]);
   //pointer/offset notation using pointer
   printf("pointer/offset notation using pointer: *(pointer + 4) = %i\n", *(pointer + 4));
   printf("\n");
   
   //entire array in 4 different ways
   printf("Array 4 ways loop: \n");
   for(i = SIZE - 1;i >= 0;i--){
      printf("subscript notation: array[%i] = %i\n",i ,array[i]);\
      printf("pointer/offset notation: *(array + %i) = %i\n",i, *(array + i));
      printf("subscript notation using pointer: pointer[%i] = %i\n",i, pointer[i]);
      printf("pointer/offset notation using pointer: *(pointer + %i) = %i\n",i, *(pointer + i));
   } 

   
   
   
   return 0;
}//end of main
