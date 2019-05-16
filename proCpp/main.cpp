#include <iostream>

struct A
{

};

struct B1
{
    int a1;
    int a2;
};

struct B2
{
    char a1;
    char a2;
};

struct B3
{
    int a1;
    char a2;
};

struct B4
{
    char a1;
    int a2;
};

struct CSI
{
    char c;
    short s;
    int i;
};

struct CIS
{
    char c;
    int i;
    short s;
};

//DIAMOND

struct teto
{
    int t;
};

struct jobb : public teto
{
    int j;
};

struct bal : public teto
{
    int b;
};

struct alja : virtual public jobb, bal
{
    int a;   
};

int main()
{
    std::cout << sizeof(A) << "\n";
    std::cout << sizeof(B1) << "\n";
    std::cout << sizeof(B2) << "\n";
    std::cout << sizeof(B3) << "\n";
    std::cout << sizeof(B4) << "\n";
    std::cout << sizeof(CSI) << "\n";
    std::cout << sizeof(CIS) << "\n";

    alja a;
    a.bal::t=9;
    a.jobb::t=8;
    a.j=7;
    a.b=6;
    a.a=5;

    getchar();
    return 0;
}