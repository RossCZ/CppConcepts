#include "stdafx.h"
#include "FunctionPointer.h"

#include <iostream>
#include <functional>

//bool numbersComparer(std::function<bool(int, int)> compFunction)
bool numbersComparer(bool(*compFunction)(int, int))
{
    // pass some random numbers to the given function pointer
    return compFunction(2, 3);
}

class MyConverteFunctions
{
public:
    static bool compareNumbers1(int a, int b)
    {
        std::cout << "compareNumbers1" << std::endl;
        return (a * 1 < b);
    }

    static bool compareNumbers2(int a, int b)
    {
        std::cout << "compareNumbers2" << std::endl;
        return (a * 2 < b);
    }

    static bool compareNumbers3(int a, int b)
    {
        std::cout << "compareNumbers3" << std::endl;
        return (a * 3 < b);
    }
};


void functionPointer()
{
    std::cout << std::endl << "Function pointer" << std::endl;

    //MyConverteFunctions fcs;

    //auto fp1 = std::bind(&MyConverteFunctions::compareNumbers1, fcs);
    numbersComparer(MyConverteFunctions::compareNumbers1);
    numbersComparer(MyConverteFunctions::compareNumbers2);
    numbersComparer(MyConverteFunctions::compareNumbers3);
}
