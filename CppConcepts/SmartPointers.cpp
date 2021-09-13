#include "stdafx.h"
#include "SmartPointers.h"

#include <iostream>

struct Base
{
    Base(int i = 0)
    {
        std::cout << "ctor Base" << std::endl;
    }

    ~Base()
    {
        std::cout << "dtor Base" << std::endl;
    }
};

struct Derived : Base
{
    Derived(int i = 0) : Base(i)
    {
        std::cout << "ctor Derived" << std::endl;
        ptr = new int(8);
        std::cout << &*ptr << " " << *ptr << std::endl;
        *ptr = 9;
    }
    ~Derived()
    {
        std::cout << "dtor Derived" << std::endl;
        delete ptr;
    }

    int* ptr;
};

std::weak_ptr<Base> globalPtr;

void one()
{
    Base* instance = new Derived();
    Derived* instance2 = (Derived*)instance;

    int* ptr = instance2->ptr;
    std::cout << &*ptr << " " << *ptr << " " << sizeof(Derived) << std::endl;

    delete instance;
    delete ptr;
}

void two()
{
    std::unique_ptr<Base> instance(new Derived());
    std::unique_ptr<Base> instance2 = std::move(instance);
}

void three()
{
    std::shared_ptr<Base> instance(new Derived());
    std::shared_ptr<Base> instance2 = instance;

    globalPtr = instance;
}

void smartPointers()
{
    std::cout << std::endl << "Smart pointers" << std::endl;

    std::cout << "*** START ***" << std::endl;
    one();
    std::cout << std::endl;
    two();
    std::cout << std::endl;
    three();
    std::cout << "*** END ***" << std::endl;
}
