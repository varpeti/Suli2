#include <iostream>
#include <stdio.h>

void asd(int a)
{
	int s = 0;
	for (int i = 5; i < 15; ++i)
	{
		s=(s+i)/(i-a);
		std::cout << s << "\n";
	}
}


int main()
{
	asd(10);
	getchar();
	return 0;
}