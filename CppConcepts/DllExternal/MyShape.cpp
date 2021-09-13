#include "stdafx.h"
#include "MyShape.h"

MyShape::MyShape(double height, double width)
{
    this->height = height;
    this->width = width;
}

double MyShape::CalculateArea()
{
    return height * width * 1.2;
}

double MyShape::CalculateAreaSquared()
{
    return CalculateArea() * CalculateArea();
}

MyShape::~MyShape()
{
}
