#include <iostream>
#include <stdio.h>

template<int N>
class A
{
public:
	enum { x=A<N-1>::x+A<N-2>::x };
};

template<>
class A<1>
{
public:
	enum {x=1};
};

template<>
class A<2>
{
public:
	enum {x=1};
};

int main()
{
   A<46> a;
   std::cout << a.x << "\n";
   getchar();
}

//1 1 2 3 5 8 13