#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "PreciseTime.h"
#include "Time.h"

using namespace std;
     //operator<< function, only used to get millisecond
	ostream &operator<<(ostream &output, const PreciseTime &p){

		output << ":" << setfill('0') << setw(2) << p.millisecond;
		return output;

	}//end operator<<
    //operator>> function, only used to input millisecond 
	istream &operator>>(istream &input, PreciseTime &p){
        
	    input >> p.millisecond;
	    input.get();
		return input; 

	}//end operator>>
    //constructor
	PreciseTime::PreciseTime(int h, int m, int s, int ms) 
	: Time(h, m, s) {

		setMillisecond(ms);

	}//end constructor 
    //gets millisecond 
	int PreciseTime::getMillisecond(){
		return millisecond;
	}//end getMillisecond();
    //sets millisecond
	PreciseTime& PreciseTime::setMillisecond(const int ms){

	  if (ms >= 0 && ms <= 999)
         millisecond = ms;
      else
         millisecond = 0;

	}//end setMillisecond();
