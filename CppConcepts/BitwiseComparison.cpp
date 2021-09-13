#include "stdafx.h"
#include "BitwiseComparison.h"

#include <iostream>

enum ELetters// : unsigned long
{
    alfa = 0x000001,
    beta = 0x000002,
    gamma = 0x000004,
    letter_a = 0x000008,
    letter_b = 0x000010,
    letter_c = 0x000020,

    // Groups
    Greek = alfa | beta | gamma,
    Latin = letter_a | letter_b | letter_c,
};


void bitwiseComparison1()
{
    std::cout << std::endl << "Bitwise comparison 1" << std::endl;
    ELetters myLetter1 = letter_a;
    ELetters myLetter2 = beta;
    ELetters greek = Greek;
    ELetters latin = Latin;

    bool isLetter1Greek = myLetter1 & Greek;
    bool isLetter1Latin = myLetter1 & Latin;
    bool isLetter2Greek = myLetter2 & Greek;
    bool isLetter2Latin = myLetter2 & Latin;

    std::cout << "Letter 1 greek/latin: " << isLetter1Greek << isLetter1Latin << std::endl;
    std::cout << "Letter 2 greek/latin: " << isLetter2Greek << isLetter2Latin << std::endl;
}

enum MyEnum
{
    NOT_DEFINED,
    A = 1, // 0000 0001
    B = 2, // 0000 0010
    C = 4, // 0000 0100
    D = 8  // 0000 1000
};

void bitwiseComparison2()
{
    std::cout << std::endl << "Bitwise comparison 2" << std::endl;
    int value = 3; // 0000 0011
    std::cout << bool(value & (MyEnum::B | MyEnum::A)) << std::endl;
}