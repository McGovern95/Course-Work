//CS 271
//Program Name: Complex.h
//@author: Christian McGovern
//@date: 4/23/17
//This program is a header file for the Complex class  
//

#ifndef COMPLEX_H

#define COMPLEX_H

#include <iostream>
using namespace std;

class Complex {

     friend ostream& operator<<( ostream& , const Complex& );
     friend istream& operator>>( istream& , Complex& );

   public:
     Complex( double = 0.0, double = 0.0 );
     Complex operator+( const Complex& ) const;
     Complex operator-( const Complex& ) const;
     Complex operator*( const Complex& ) const;
     Complex operator/( const Complex& ) const;

       Complex& setReal( double );
       Complex& setImaginary ( double );
       double getReal ( ) const;
       double getImaginary ( ) const;
     
   private:
     double real;
     double imaginary;

}; // end class

#endif
