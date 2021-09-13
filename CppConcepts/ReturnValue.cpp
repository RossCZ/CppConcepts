#include "stdafx.h"
#include "ReturnValue.h"

#include <iostream>
#include <vector>

class MyClass
{
public:
    static bool OutVector(std::vector<int>& result)
    {
        for (int i = 0; i < 10; i++)
        {
            result.push_back(i);
        }
        std::cout << "adress func: " << &result << " " << &result.front() << std::endl;
        return true;
    }

    static std::vector<int> ReturnVector()
    {
        std::vector<int> result;
        for (int i = 0; i < 10; i++)
        {
            result.push_back(i);
        }
        std::cout << "adress func: " << &result << " " << &result.front() << std::endl;
        return result;
    }

    static std::vector<int>& ReturnVectorRef()
    {
        std::vector<int> result;
        for (int i = 0; i < 10; i++)
        {
            result.push_back(i);
        }
        std::cout << "adress func: " << &result << " " << &result.front() << std::endl;
        return result;  // warning - returning adress of local variable
    }
};

class Item
{
public:
    int id;
};

class MyClassTwo
{
public:
    MyClassTwo()
    {
        myItem.id = 3;
    }

    Item& GetItem()
    {
        std::cout << "adress func: " << &myItem << " " << myItem.id << std::endl;
        return myItem;
    }

    Item myItem;
};

void returnValue()
{
    std::cout << std::endl << "Return value" << std::endl;

    std::cout << "Return static reference (deleted)" << std::endl;
    std::vector<int>& result = MyClass::ReturnVectorRef();
    std::cout << "adress main: " << &result << " " << result.size() << std::endl;

    std::cout << "Return copy (RVO)" << std::endl;
    std::vector<int> result1 = MyClass::ReturnVector();
    std::cout << "adress main: " << &result1 << " " << &result1.front() << std::endl;

    std::cout << "Return as out parameter" << std::endl;
    std::vector<int> result2;
    if (MyClass::OutVector(result2))
    {
        std::cout << "adress main: " << &result2 << " " << &result2.front() << std::endl;
    }

    // example 2
    std::cout << std::endl;
    std::cout << "Return member reference" << std::endl;
    MyClassTwo aClass;
    Item& anItem = aClass.GetItem();
    std::cout << "adress main: " << &anItem << " " << anItem.id << std::endl;
}
