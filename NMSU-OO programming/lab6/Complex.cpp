//CS 271
//Program Name: Complex.cpp
//@author: Christian McGovern
//@date: 4/23/17
//This program demonstrates futher understanding of classes 
//and  binary operator overloading 

#include <iostream>
#include <cmath>
#include "Complex.h"
using namespace std;

      ostream& operator<<( ostream& output, const Complex& obj ) {

     //  your statements should display the number in the form a + bi  (if b is positive)
     //  or a - bi (if b is negative)
        if(obj.imaginary >= 0)
            output << obj.real << " + " << obj.imaginary << "i";
        else 
            output << obj.real << " - " << abs(obj.imaginary) << "i";

        return output; 



     } // end operator<<

     istream& operator>>( istream& input, Complex& obj) {

     // your statements should input the real and imaginary values
     // don't display prompts
        input >> obj.real >> obj.imaginary;
        return input; 

     } // end operator>>

// member functions

     Complex::Complex( double r , double i ) {

       real = r;
       imaginary = i;

     } // end constructor
 
     double Complex::getReal( ) const {

        return real;
     }

     double Complex::getImaginary ( ) const {

        return imaginary;
     }

     Complex& Complex::setReal ( double r ) {

        real = r;

     }

     Complex& Complex::setImaginary ( double i ) {

        imaginary = i;

     }

     Complex Complex::operator+( const Complex& x ) const {

        Complex sum( real + x.real, imaginary + x.imaginary );
        return sum;

     } // end operator+

     // your code for the subtraction operator goes here
     Complex Complex::operator-(const Complex &x) const{

        Complex difference(real - x.real, imaginary - x.imaginary);
        return difference;

     }//end operator- 
     // your code for the multiplication operator goes here
     Complex Complex::operator*(const Complex &x) const{
       
        Complex product;
        product.real = real * x.real - imaginary * x.imaginary;
        product.imaginary = real * x.imaginary + imaginary * x.imaginary;
        return product;  

     }//end operator* 
     // your code for the division operator goes here
      Complex Complex::operator/(const Complex &x) const{

        double denom = x.real * x.real + x.imaginary * x.imaginary;
        Complex quotient;
        quotient.real = real * x.real + imaginary * x.imaginary;
        quotient.imaginary = imaginary * x.real - real * x.imaginary;
        quotient.real = quotient.real / denom;
        quotient.imaginary = quotient.imaginary / denom;
        return quotient;

      }//end operator/


 














