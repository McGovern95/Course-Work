#ifndef SYMTABLE
#define SYMTABLE

void Insert(char *, int);
//void Display();
//void Delete();
int Search(char lab[]);
//void Modify();
char fetch(char *);
struct SymbTab{
	char label[10],symbol[10];
	int addr;
	struct SymbTab *next;
};
struct SymbTab *first,*last;

#endif