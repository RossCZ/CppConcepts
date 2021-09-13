#include "stdafx.h"
#include "AddressModification.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void addressModification()
{
    std::cout << std::endl << "Address modification" << std::endl;
    // create pointer to int on heap
    const int* x = new int(5);
    // *x = 3; - this fails because it's constant
    cout << "X value (const int): " << *x << endl;

    // save address as a string 
    ostringstream getTheAdress;
    getTheAdress << x;
    string address = getTheAdress.str();

    cout << "X adress: " << address << endl;

    // convert address to base 16
    // sometimes causes out of range exception - works only on x86 build
    int hexAddress = stoi(address, 0, 16);

    // make a new pointer (warning - type cast conversion from greater size)
    int* newPtr = (int*)hexAddress;

    // can now change value of x 
    *newPtr = 3;

    cout << "X value (modified): " << *x << endl;
}