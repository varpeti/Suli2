#include <iostream>
#include <stdio.h>
#include <map>

class A
{
public:
    virtual std::string name() const = 0;
    virtual A* clone() = 0;
};

class B : public A
{
public:
    virtual std::string name() const {return "B";}
    virtual A* clone() {return new B();}
};

class C : public A
{
public:
    virtual std::string name() const {return "C";}
    virtual A* clone() {return new C();}
};

class Manager
{
public:
    std::map<std::string, A*> m;
    void reg(A *a, std::string s);
    A* create(std::string s) const;
};

void Manager::reg(A *a, std::string s)
{
    m[s]=a;
}

A* Manager::create(std::string s) const 
{
    return m.at(s)->clone();
}


int main()
{
    Manager man;
    man.reg(new B(),"B");
    man.reg(new C(),"C");

    A* b = man.create("B");
    A* c = man.create("C");
    std::cout << b->name() << " " << c->name() << "\n";


    getchar();
    return 0;
}