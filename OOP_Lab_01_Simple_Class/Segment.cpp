#include <iostream>
#include "Segment.h"

using namespace std;

Segment::Segment(double x1Val, double y1Val, double x2Val, double y2Val)
{
    x1 = x1Val;
    y1 = y1Val;
    x2 = x2Val;
    y2 = y2Val;
}

void Segment::read()
{
    cin >> x1 >> y1 >> x2 >> y2;
}

void Segment::print() const
{
    cout << "[(" << x1 << ", " << y1 << ") ; (" << x2 << ", " << y2 << ")]";
}

double Segment::getX1() const 
{ 
    return x1; 
}

void Segment::setX1(double newValue) 
{
    x1 = newValue;
}

double Segment::getY1() const
{ 
    return y1;
}

void Segment::setY1(double newValue) 
{ 
    y1 = newValue;
}

double Segment::getX2() const 
{ 
    return x2;
}

void Segment::setX2(double newValue) 
{ 
    x2 = newValue; 
}

double Segment::getY2() const 
{ 
    return y2;
}

void Segment::setY2(double newValue) 
{ 
    y2 = newValue;
}