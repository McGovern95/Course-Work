#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Time.h"

using namespace std;

   // overloaded output operator - friend function

   ostream &operator<<( ostream &output, const Time & t) {
      output << setfill('0') << setw(2) << t.hour;
      output << ":" << setfill('0') << setw(2) << t.minute;
      output << ":" << setfill('0') << setw(2) << t.second;
      return output;
   }

   // overloaded output operator - friend function
   //
   // the get function extracts one character from the input stream
   //
   // it is used in this function to "skip" the colons between parts of the time

   istream &operator>>( istream &input, Time &t ) {
      input >> t.hour;
      input.get();
      input >> t.minute;
      input.get();
      input >> t.second;
      return input;
   }


   // another constructor

   Time::Time (int h, int m, int s) {
      
     setHour(h);
     setMinute(m);
     setSecond(s);
   }

   // mutator for hour

   Time& Time::setHour( const int h ) {
      if (h >= 1 && h <= 12)
         hour = h;
      else
         hour = 1;
   }
   
   // mutator for minute

   Time& Time::setMinute( const int m ) {
      if (m >= 0 && m <= 59)
         minute = m;
      else
         minute = 0;
   }

   // mutator for minute

   Time& Time::setSecond( const int s) {
      if (s >= 0 && s <= 59)
         second = s;
      else
         second = 0;
   }

   // accessor for hour

   int Time::getHour ( ) const {
      return hour;
   }

   // accessor for hour

   int Time::getMinute ( )  const{
      return minute;
   }

   // accessor for hour

   int Time::getSecond ( )  const{
       return second;
   }
 




