#include <iostream>
int main()
{
	int *a = new int[10];

	#pragma omp parallel for
    for (int i = 0; i < 10; ++i)
    {
    	a[i]=99;
    }
    for (int i = 0; i < 10; ++i)
    {
    	std::cout << a[i] << "\n";
    }
}