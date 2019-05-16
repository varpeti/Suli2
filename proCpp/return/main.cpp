#include <iostream>
#include <stdio.h>

struct A
{
	int i;
	A(const A &a) {i=a.i+1; std::cout<<this<<" cp"<<"\n"; };
	A(int i) : i(i) {};
};

A fun1()
{
	A a(10);
	a.i=99;
	return a;
};

A fun2()
{
	return fun1();
};

int main()
{
	A a = fun2();
	std::cout<< &a << " " << a.i << "\n";
	A b(a);
	std::cout<< &b << " " << b.i << "\n";

	getchar();
	return 0;
}