// BankAccount.h 
// Class definition file for the BankAccount class

// this is a C++ program

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class BankAccount {

public:
   BankAccount( string f, string l, int n );
   void setFirstName( string f );
   void setLastName( string l );
   void setAccountNumber ( int n );
   string getFirstName( );
   string getLastName( );
   int getAccountNumber ( );
   //my display(); 
   void display();

private:
   string firstName;
   string lastName;
   int accountNumber;
};

#endif

