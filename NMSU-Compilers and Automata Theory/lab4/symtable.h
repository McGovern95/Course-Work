#ifndef SYMTABLE
#define SYMTABLE

void Insert();
void Display();
void Delete();
int Search(char lab[]);
void Modify();
struct SymbTab{
	char label[10],symbol[10];
	int addr;
	struct SymbTab *next;
};
struct SymbTab *first,*last;

#endif