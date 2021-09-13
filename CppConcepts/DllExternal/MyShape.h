#pragma once

class __declspec(dllexport) MyShape
{
public:
    double height;
    double width;
    int id;

    MyShape(double height, double width);

    double CalculateArea();
    double CalculateAreaSquared();

    ~MyShape();
};

