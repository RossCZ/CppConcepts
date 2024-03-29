#include "stdafx.h"

#include "AddressModification.h"
#include "ArrayTest.h"
#include "BitwiseComparison.h"
#include "Containers.h"
#include "CustomComparator.h"
#include "DllTest.h"
#include "FloatVsDouble.h"
#include "FunctionPointer.h"
#include "MoveSemantics.h"
#include "NRVO.h"
#include "Pointers.h"
#include "OperatorOverloading.h"
#include "ReturnValue.h"
#include "SmartPointers.h"
#include "TemplateMultidimensionalInterpolation.h"
#include "Threading.h"
#include "ThreadPool.h"
#include "VoidPointer.h"

#include <iostream>

int main()
{
    std::cout << std::endl << "Concepts of C++ programming language" << std::endl;

    //addressModification();
    //arrayTest();
    //bitwiseComparison1();
    //bitwiseComparison2();
    //containers();
    //customComparator();
    //dllTest();
    //floatVsDouble();
    //functionPointer();
    //moveSemantics();
    //nrvo();
    //operatorOverloading();
    //pointers1();
    //pointers2();
    //returnValue();
    //smartPointers();
    templateMultidimensionalInterpolation();
    //threading();
    //threadPool();
    //voidPointer();

    // keep console window open
    int res;
    std::cin >> res;
}