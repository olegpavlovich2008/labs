#include <iostream>
#include <cmath>
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

double Segment::length() const
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void Segment::printPointInRatio(double lambda) const
{
    if (abs(lambda + 1.0) < 0.000001)
    {
        cout << "Ошибка: значение не может быть равно -1.";
        return;
    }

    double rx = (x1 + lambda * x2) / (1.0 + lambda);
    double ry = (y1 + lambda * y2) / (1.0 + lambda);

    cout << "(" << rx << ", " << ry << ")";
}

bool Segment::operator==(const Segment& other) const
{
    return abs(length() - other.length()) < 0.000001;
}

bool Segment::isParallelToOx() const
{
    bool sameY = (abs(y1 - y2) < 0.000001);
    bool differentX = (abs(x1 - x2) > 0.000001);

    return (sameY && differentX);
}

bool Segment::isParallelTo(const Segment& other) const
{
    double dx1 = x2 - x1;
    double dy1 = y2 - y1;
    double dx2 = other.x2 - other.x1;
    double dy2 = other.y2 - other.y1;

    return (abs(dx1 * dy2 - dy1 * dx2) < 0.000001);
}

bool Segment::intersectsOy() const
{
    return ((x1 * x2 < 0) || ((abs(x1) < 0.000001) || (abs(x2) < 0.000001)));
}

bool Segment::intersectsLine(double A, double B, double C) const
{
    double val1 = A * x1 + B * y1 + C;
    double val2 = A * x2 + B * y2 + C;

    if (abs(val1) < 0.000001)
    {
        val1 = 0.0;
    }
    if (abs(val2) < 0.000001)
    {
        val2 = 0.0;
    }

    return (val1 * val2 <= 0.0);
}

bool Segment::containsPoint(double px, double py) const
{
    double val = (x2 - x1) * (py - y1) - (y2 - y1) * (px - x1);

    if (abs(val) > 0.000001)
    {
        return false;
    }

    bool insideX = abs(abs(px - x1) + abs(px - x2) - abs(x1 - x2)) < 0.000001;
    bool insideY = abs(abs(py - y1) + abs(py - y2) - abs(y1 - y2)) < 0.000001;

    return (insideX && insideY);
}

double Segment::getRatioOfPoint(double px, double py) const
{
    if (!containsPoint(px, py))
    {
        cout << "Ошибка: точка не принадлежит отрезку.";
        return 0;
    }

    if (abs(px - x2) < 0.000001 && abs(py - y2) < 0.000001)
    {
        cout << "Ошибка: точка совпадает с концом отрезка.";
        return 0;
    }

    if (abs(x2 - x1) > abs(y2 - y1))
    {
        return (px - x1) / (x2 - px);
    }
    else
    {
        return (py - y1) / (y2 - py);
    }
}

Segment Segment::operator*(double k) const
{
    double newX2 = x1 + k * (x2 - x1);
    double newY2 = y1 + k * (y2 - y1);

    return Segment(x1, y1, newX2, newY2);
}