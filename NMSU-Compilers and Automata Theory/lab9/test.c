int x;
int y[10];

int sumArray(void)
{
	int i;
	int sum;
	sum = 0;
	i = 1;
	while (i <= 10)
	{
		sum = sum + y[i];
		i = i + 1;
	}
	write sum;
	return sum;
}

int foo(int x, int y){
	write "x";	
	write x;
	write "y";
	write y;
	return x*y;
}


int main(void)
{	
	int a;
	int b;
	int i;
	i = 1;
	read a;
	b = 10;
	write "Testing Function Returns";
	write foo(a,foo(i,b));
	write "Array fill test";
	while (	i <= 10)
	{
		y[i + 1 - 1] = i;
		i = i + 1;
	}
	write 1+2+3+4+5+6+7+8+9+10;
	if(sumArray()==55){
		write "equals 55";
	}
	else
	{
		write "nequals 55";
	}

	if(sumArray()!=0){
		write "nequals 0";
	}
	else
	{
		write "equals 55";
	}

	
}