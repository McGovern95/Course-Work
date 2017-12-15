all: lab4b

lab4b: BankAccount.o lab4b.o 
		g++ BankAccount.o lab4b.o -o lab4b

lab4b.o: lab4b.cpp BankAccount.h
		g++ -c lab4b.cpp

BankAccount.o:	BankAccount.cpp BankAccount.h
				g++ -c BankAccount.cpp