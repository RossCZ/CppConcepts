#include "stdafx.h"
#include "OperatorOverloading.h"

#include <iostream>

class MyClass
{
public:
    MyClass(int first, int second)
    {
        this->first = first;
        this->second = second;
    }

    int first;
    int second;

    bool operator==(const MyClass& other) const
    {
        return this->first == other.first && this->second == other.second;
    }
};

class HelperClass
{
    bool equals(const MyClass& obj, const MyClass& other) const
    {
        return obj.first == other.first && obj.second == other.second;
    }
};

void operatorOverloading()
{
    std::cout << std::endl << "Operator overloading" << std::endl;
    MyClass obj1(1, 3);
    MyClass obj2(1, 3); //(-2, 3);
    bool equal = obj1 == obj2;
    std::cout << "object are equal: " << equal << std::endl;
}
