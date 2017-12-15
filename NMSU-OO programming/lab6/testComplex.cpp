//CS 271
//Program Name: testComplex.cpp
//@author: Christian McGovern
//@date: 4/23/17
//This program tests the diffrent operator overloading functions 
//located in the Complex class 


#include <iostream>
#include "Complex.h"
using namespace std;

int main ( ) {

   // create two complex objects

   Complex num1 ( 3, 4 );
   Complex num2 ( 1, 3 );

   // test the addition operator
   Complex sum = num1 + num2;
   cout << "The result of adding 3 + 4i to 1 + 3i is " << sum.getReal() << " + " << sum.getImaginary() << "i" << endl;

   // test the output stream operator
   cout << "testing the output stream operator: ";
   cout << sum;
   cout << endl; 

   // test the subtraction operator
   Complex difference = num1 - num2;
   // display the results
   cout << "The result of subracting 3 + 4i to 1 + 3i is "; 
   cout << difference;
   cout << endl; 

   // test the multiplication operator
   Complex product = num1 * num2;
   // display the results
   cout << "The result of multiplying 3 + 4i to 1 + 3i is "; 
   cout << product; 
   cout << endl;

   //test the input stream operator 
   cout << "Testing the input stream operator: ";
   Complex test;
   cin >> test;
   cout << endl;
   cout << "You entered: "; 
   cout << test; 
   cout << endl; 


   // test the division operator
   Complex quotient = num1 / num2;
   // display the results
   cout << "The result of dividing 3 + 4i to 1 + 3i is "; 
   cout << quotient; 
   cout << endl;

} // end main
   
