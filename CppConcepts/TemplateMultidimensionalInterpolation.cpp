#include "stdafx.h"
#include <iostream>
#include <vector>

template <class N>
struct is_vector_void { static const int value = 0; };

template <class N>
struct is_vector_void<std::vector<N>> { static const int value = 1; };

template<typename T>
struct is_vector_return : std::false_type {};

template<typename T, typename A>
struct is_vector_return<std::vector<T, A>> : std::true_type {};

// print vector of numbers
template <typename T>
std::enable_if_t<!is_vector_void<typename T::value_type>::value>
printVector(T const& v)
{
    std::cout << "{";
    for (unsigned int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i];
        if (i != v.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "}";
}

// print vector of vectors
template <typename T>
std::enable_if_t<is_vector_void<typename T::value_type>::value>
printVector(T const& v)
{
    std::cout << "{";
    for (const auto& inner : v)
    {
        printVector(inner);
    }
    std::cout << "}";
}

// interpolate two numbers according to ratio
template <typename T>
std::enable_if_t<!is_vector_return<typename T>::value, T>
interpolate(T const& a, T const& b, double ratio)
{
    const double result = (b - a) * ratio + a;

    std::cout << "interpolating numbers: " << a << " " << b << " (" << ratio << ")" << std::endl;
    std::cout << "\tresult: " << result << std::endl;

    return { result };
}

// interpolate two vectors according to ratio
template <typename T>
std::enable_if_t<is_vector_return<typename T>::value, T>
interpolate(T const& a, T const& b, double ratio)
{
    std::cout << "interpolating vectors:" << std::endl;
    std::cout << "\t"; printVector(a); std::cout << std::endl;
    std::cout << "\t"; printVector(b); std::cout << std::endl;

    T resultVector;
    for (unsigned int i = 0; i < a.size(); i++)
    {
        const auto result = interpolate(a[i], b[i], ratio);
        resultVector.push_back(result);
    }

    return resultVector;
}

// interpolate vector of numbers numbers
template <typename T>
std::enable_if_t<!is_vector_void<typename T::value_type>::value>
interpolateData(T const& data, const std::vector<double>& ratios, int& ratioIndex)
{
    const auto result = interpolate(data[0], data[1], ratios[ratioIndex]);

    std::cout << std::endl << "\t*** RESULT IS: " << result << std::endl;
}

// interpolate vector of vectors
template <typename T>
std::enable_if_t<is_vector_void<typename T::value_type>::value>
interpolateData(T const& data, const std::vector<double>& ratios, int& ratioIndex)
{
    std::cout << std::endl << "interpolateData:" << std::endl;
    std::cout << "\t"; printVector(data); std::cout << std::endl;

    const auto result = interpolate(data[0], data[1], ratios[ratioIndex]);
    ratioIndex++; // increment index of ratio for next dimension
    interpolateData(result, ratios, ratioIndex);
}

void templateMultidimensionalInterpolation()
{
    // data to be interpolated - multidimensional vector
    const std::vector<std::vector<std::vector<double>>> data
    {
        { { 100, 200 }, { 300, 400 } },
        { { 500, 600 }, { 700, 800 } }
    };
    const std::vector<std::vector<std::vector<double>>> data2
    {
        { { 10, 20 }, { 30, 40 } },
        { { 50, 60 }, { 70, 80 } }
    };
    const std::vector<std::vector<std::vector<std::vector<double>>>> data3 = { data, data2 };

    // ratios according to which interpolate each dimension of data
    const std::vector<double> ratios = { 0.1, 0.2, 0.3 };
    const std::vector<double> ratios2 = { 0.1, 0.2, 0.3, 0.4 };
    // index of the ratio for the first dimension
    int index = 0;
    int index2 = 0;

    interpolateData(data, ratios, index);
    interpolateData(data3, ratios2, index2);
}
