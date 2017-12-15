//definitions 
#ifndef PRECISETIME_H
#define PRECISETIME_H
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Time.h"
using namespace std;

class PreciseTime : public Time{
  //friend operator overloaders 
  friend ostream &operator<<( ostream &, const PreciseTime &);
  friend istream &operator>>( istream &, PreciseTime &);
   //public functions 
   public: 
   	PreciseTime(int h = 1, int m = 0, int s = 0, int ms = 0);
   	int getMillisecond();
   	PreciseTime &setMillisecond(const int ms);
   //private data members 
   private: 
   	int millisecond; 

};//end class
#endif