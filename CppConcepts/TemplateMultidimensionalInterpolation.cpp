#include "stdafx.h"
#include "TemplateMultidimensionalInterpolation.h"

#include <vector>
#include <iostream>

template <class N>
struct is_vector { static const int value = 0; };

template <class N>
struct is_vector<std::vector<N>> { static const int value = 1; };

template<typename>
struct is_std_vector : std::false_type {};

template<typename T, typename A>
struct is_std_vector<std::vector<T, A>> : std::true_type {};

template <typename T>
std::enable_if_t<is_vector<typename T::value_type>::value>
interpolateData(T const& data, const std::vector<double>& ratios, int& ratioIndex)
{
    std::cout << std::endl << "interpolateData " << ratios.size() << " not a result" << std::endl;

    auto res = interpolate(data[0], data[1], ratios[ratioIndex]);
    ratioIndex++;
    interpolateData(res, ratios, ratioIndex);
}

template <typename T>
std::enable_if_t<!is_vector<typename T::value_type>::value>
interpolateData(T const& data, const std::vector<double>& ratios, int& ratioIndex)
{
    std::cout << std::endl << "interpolateData " << "RESULT IS " << interpolate(data[0], data[1], ratios[ratioIndex]) << std::endl;
}

template <typename T>
std::enable_if_t<is_std_vector<typename T>::value, T>
interpolate(T const& a, T const& b, double ratio)
{
    std::cout << "interpolating vectors " << a.size() << " " << b.size() << std::endl;

    T res;
    for (unsigned int i = 0; i < a.size(); i++)
    {
        auto result = interpolate(a[i], b[i], ratio);
        res.push_back(result);
    }

    return res;
}

template <typename T>
std::enable_if_t<!is_std_vector<typename T>::value, T>
interpolate(T const& a, T const& b, double ratio)
{
    std::cout << "interpolating numbers " << a << " " << " " << b << " " << ratio << std::endl;
    double res = (b - a) * ratio + a;
    std::cout << "res " << res << std::endl;
    return { res };
}

void templateMultidimensionalInterpolation()
{
    std::cout << std::endl << "Template Multidimensional Interpolation" << std::endl;

    std::vector<std::vector<std::vector<double>>> data
    {
        { { 100, 200 },{ 300, 400 } },
        { { 500, 600 },{ 700, 800 } }
    };
    std::vector<std::vector<std::vector<double>>> data2
    {
        { { 10, 20 },{ 30, 40 } },
        { { 50, 60 },{ 70, 80 } }
    };
    std::vector<std::vector<std::vector<std::vector<double>>>> data3 = { data, data2 };

    std::vector<double> ratios = { 0.1, 0.2, 0.3 };
    std::vector<double> ratios2 = { 0.1, 0.2, 0.3, 0.4 };
    int index = 0;
    int index2 = 0;

    //interpolateData(data, ratios, index);
    //interpolateData(data3, ratios2, index2);

    std::vector<double> data1D{ 100, 200 };
    std::vector<double> ratios1D = { 0.1 };
    int index1D = 0;
    interpolateData(data1D, ratios1D, index1D);
}