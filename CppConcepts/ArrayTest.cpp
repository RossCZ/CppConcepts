#include "stdafx.h"
#include "ArrayTest.h"

#include <vector>
#include <iostream>

void numberToBinary(int n)
{
    int i;
    int noBits = 4;  // print formatting
    for (i = 1 << (noBits - 1); i > 0; i = i / 2)
    {
        ((n & i) != 0) ? std::cout << "1" : std::cout << "0";
    }
}

void arrayTest()
{
    std::cout << std::endl << "Array test" << std::endl;

    std::cout << std::endl << "size of basic types (may differ on different hardware)" << std::endl;
    std::cout << "int: " << sizeof(int) << std::endl;
    std::cout << "long: " << sizeof(long) << std::endl;
    std::cout << "long long: " << sizeof(long long) << std::endl;
    std::cout << "int8_t: " << sizeof(int8_t) << std::endl;
    std::cout << "int16_t: " << sizeof(int16_t) << std::endl;
    std::cout << "int32_t: " << sizeof(int32_t) << std::endl;
    std::cout << "int64_t: " << sizeof(int64_t) << std::endl;

    std::vector<int16_t> xVec = { 1, 0, 2 };
    int16_t* a = &xVec[0];
    int32_t* b = (int32_t*)a;
    int64_t* c = (int64_t*)a;

    std::cout << std::endl << "array of ints" << std::endl;
    for (const auto& x : xVec)
    {
        std::cout << x << " ";
        numberToBinary(x);
        std::cout << std::endl;
    }

    std::cout << std::endl <<"interpreting first 2, 4, 8 bytes" << std::endl;
    std::cout << *a << std::endl;
    std::cout << *b << std::endl;
    std::cout << *c << std::endl;

    std::cout << std::endl << "moving pointer out of the array" << std::endl;
    a++;
    a++;
    a++;
    std::cout << *a << std::endl;
}