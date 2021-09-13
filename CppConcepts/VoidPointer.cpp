#include "stdafx.h"
#include "VoidPointer.h"

#include <iostream>
#include <unordered_map>

class MyClass
{
};

class YourClass
{
};

class Mapper
{
public:
    void add(void* k, void* v)
    {
        m_map[k] = v;
    }

    std::unordered_map<void*, void*> m_map;
};

void voidPointer()
{
    std::cout << std::endl << "Void pointer" << std::endl;

    MyClass* mc = new MyClass();
    YourClass* yc = new YourClass();

    std::cout << mc << "\n";
    std::cout << yc << "\n";
    std::cout << "\n";

    Mapper m;
    m.add(mc, yc);
    m.add(yc, mc);

    for (auto entry : m.m_map)
    {
        std::cout << entry.first << "\n";
    }
}