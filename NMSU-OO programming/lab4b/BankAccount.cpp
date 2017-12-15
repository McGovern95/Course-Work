// BankAccount.cpp 
// Function definitions file for the BankAccount class

// this is a C++ program

#include <iostream>
#include <string>
#include "BankAccount.h"

using namespace std;

// Implementation of the BankAccount class 
//
// contains member function definitions


   BankAccount::BankAccount( string f, string l, int n ){
     setFirstName(f);
     setLastName(l);
     setAccountNumber(n);

   } // end constructor

   void BankAccount::setFirstName( string f ) {
     firstName = f;
   }

   void BankAccount::setLastName( string l ) {
     lastName = l;
   }

   void BankAccount::setAccountNumber ( int n ) {
     accountNumber = n;
   }
   string BankAccount::getFirstName( ) {
      return firstName;
   }

   string BankAccount::getLastName( ) {
      return lastName;
   }

   int BankAccount::getAccountNumber ( ) {
      return accountNumber;
   }
   //my display function
   void BankAccount::display(){
       //printed in the format from the instructions 
      cout << "Customer: " << firstName << " " << lastName << endl;
      cout << "Account: " << accountNumber << endl;
      cout << endl;


   }//end display

