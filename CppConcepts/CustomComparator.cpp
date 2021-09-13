#include "stdafx.h"
#include "CustomComparator.h"

#include <iostream>
#include <set>
#include <map>

struct CustomCompare
{
    bool operator()(const int& a, const int& b)
    {
        return a < b;
    }

    bool operator()(const double& a, const double& b)
    {
        const double tol = 1e-3;
        return (a < b) && !(fabs(a - b) < tol);
    }
};

void customComparator()
{
    std::cout << std::endl << "Custom comparator" << std::endl;

    std::set<int, CustomCompare> setOfInts;
    setOfInts.insert(2);
    setOfInts.insert(5);
    setOfInts.insert(2);

    std::set<double, CustomCompare> setOfDoubles;
    setOfDoubles.insert(2.0001);
    setOfDoubles.insert(5.0);
    setOfDoubles.insert(2.0002);

    std::cout << "Ints" << std::endl;
    for (const auto& val : setOfInts)
    {
        std::cout << "\t" << val << std::endl;
    }

    std::cout << "Doubles" << std::endl;
    for (const auto& val : setOfDoubles)
    {
        std::cout << "\t" << val << std::endl;
    }

    // custom comparator inside a lambda -> compiler error in some compilers (bug)
    // e.g. x64 MSVC v19.14 (VS 2017 v. 15.7.4)
    // Compiler explorer: godbolt.org
    //auto myLambda = []()
    //{
    //    auto comparator = [tolerance = 0.01](const double& a, const double& b)
    //    {
    //        return (a + tolerance) < b;
    //    };

    //    std::map<double, double, decltype(comparator)> mapOfNumbers(comparator);

    //    auto myInnerLambda = [&mapOfNumbers](double a, double b)
    //    {
    //        mapOfNumbers[a] += b;
    //    };
    //};
}
