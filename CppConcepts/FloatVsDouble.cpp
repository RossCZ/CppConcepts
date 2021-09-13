#include "stdafx.h"
#include "FloatVsDouble.h"

#include <iostream>

using namespace std;

void printNumber(float number)
{
    cout << "inside function " << number << endl;
}

void floatVsDouble()
{
    //double n1 = std::numeric_limits<double>::infinity();
    double n1 = 1.234567890123;
    cout.precision(17);
    cout << "outside function " << n1 << endl;
    printNumber(n1); // warning - possible loss of data


    //float n2 = std::numeric_limits<float>::infinity();
    float n2 = 1234567890123.0; // warning - initializing from double to float
    cout.precision(17);
    cout << "outside function " << n2 << endl;
    printNumber(n2);
}
