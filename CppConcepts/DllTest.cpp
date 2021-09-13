#include "stdafx.h"
#include "DllTest.h"

#include <iostream>
#include "DllExternal\MyShape.h"

void dllTest()
{
    std::cout << std::endl << "DLL test" << std::endl;

    // two step compilation required:
    // build DllExternal
    // move DllExternal from the build directory to the CppConcepts directory (one level up)
    // build CppConcepts
    MyShape myShape(5.5, 2.2);
    std::cout << myShape.CalculateArea();
}
