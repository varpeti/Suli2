#include <iostream>
#include <stdio.h>

int i;

class A
{
public:
	bool isOK;
	int last;
	A() 
	{
		isOK=false;
		last=0;
	};

	void ch(int _i)
	{
		last = i;
		i = _i;
	};

	~A()
	{
		if(!isOK)
		{
			i=last;
		}
	};
};

void asd(int j)
{
		A a = A();

		a.ch(j);
		if (i<30) a.isOK=true;
}


int main()
{
	asd(40);
	std::cout << i << "\n";
	
	asd(20);
	std::cout << i << "\n";

	asd(40);
	std::cout << i << "\n";
	

	getchar();
	return 0;
}