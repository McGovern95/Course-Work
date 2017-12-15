#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Time {

  friend ostream &operator<<( ostream &, const Time & );
  friend istream &operator>>( istream &, Time &);

  private:
    int hour;
    int minute;
    int second;

  public:
    Time (int h=1, int m=0, int s=0);
    Time& setHour( const int );
    Time& setMinute( const int );
    Time& setSecond( const int );
    int getHour ( ) const;
    int getMinute ( ) const;
    int getSecond ( ) const;
 
};
#endif




