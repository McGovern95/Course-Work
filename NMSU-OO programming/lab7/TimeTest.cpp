//CS 271
//Program Name: TimeTest.cpp
//@author: Christian McGovern
//@date: 4/29/17
//This program demonstrates inheritance and derived classes

#include "Time.h"
#include "PreciseTime.h"
#include <string>
#include <sstream>

using namespace std;


int main ( ) {

   Time j ( 4, 5, 10);
   Time t;
   cout << "Input a time in the format hh:mm:ss ";
   cin >> t;
   cout << "j is " << j << endl;
   cout << "t is " << t << endl;
    //my code
    //creating two PreciseTime objects
    PreciseTime test(4,5,20,23);
    PreciseTime k;
    //testing the input overloader 
    cout << "Input Precise Time in the format hh:mm:ss:ms ";
    cin >> (Time&)k;
    cin >> k;
    //testing the output overloader
    cout << "test is " << (Time&)test << test << endl;
    cout << "k is " << (Time&)k << k << endl;
    //testing the mutator and accessor 
    test.setMillisecond(998);
    cout << "setMillisecond test (998): " << endl;
    cout << test.getMillisecond() << endl; 


}//end main
