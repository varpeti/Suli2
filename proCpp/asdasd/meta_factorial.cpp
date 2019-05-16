#include <iostream>
#include <stdio.h>

template<int N>
class A
{
public:
	enum { x=A<N-1>::x*N };
};

template<>
class A<0>
{
public:
	enum {x=1};
};

int main()
{
   A<5> a;
   std::cout << a.x << "\n";
   getchar();
}