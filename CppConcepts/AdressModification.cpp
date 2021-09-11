#include "stdafx.h"
#include "AdressModification.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void adressModification()
{
    // create pointer to int on heap
    const int* x = new int(5);
    // *x = 3; - this fails because it's constant
    cout << "X value (const int): " << *x << endl;

    // save address as a string 
    ostringstream get_the_address;
    get_the_address << x;
    string address = get_the_address.str();

    cout << "X adress: " << address << endl;

    // convert address to base 16
    int hex_address = stoi(address, 0, 16);

    // make a new pointer 
    int* new_pointer = (int*)hex_address;

    // can now change value of x 
    *new_pointer = 3;

    cout << "X value (modified): " << *x << endl;
}