#include "stdafx.h"
#include "Pointers.h"

#include <iostream>

class Base
{
public:
    virtual void Moo()
    {
        std::cout << "Base moo!\n";
    }
};

class Derived : public Base
{
public:
    virtual void Moo() override
    {
        std::cout << "Derived moo!\n";
    }
};

void pointers1()
{
    std::cout << std::endl << "Pointers 1" << std::endl;

    Base* base = new Base();
    Derived* derived = new Derived();
    Base* base2 = derived;
    Base* base3 = &*derived;

    bool equal = (base == derived);
    bool equal2 = (base2 == derived);
    bool equal3 = (base3 == derived);

    Base* base4 = new Derived();
    base4->Moo();
    Derived* derived4 = (Derived*)(base4);
    derived4->Moo();

    // reference test
    int a = 10;
    int& b = a;
    int* c = &a;
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
    std::cout << b << std::endl;
    std::cout << &b << std::endl;
    std::cout << c << std::endl;
    std::cout << &c << std::endl;
    std::cout << *c << std::endl;
    std::cout << &*c << std::endl;
}

void pointers2()
{
    std::cout << std::endl << "Pointers 2" << std::endl;

    int* i;

    {
        int a = 5;
        i = &a;
    }

    int* j = i;
    std::cout << &i << std::endl;
    std::cout << i << std::endl;
    std::cout << *i << std::endl;
    std::cout << &j << std::endl;
    std::cout << j << std::endl;

    *j = 15;

    std::cout << *j << std::endl;
    //std::cout << a << std::endl;
}