#pragma once

class Segment
{
public:

    Segment(double x1Val = 0.0, double y1Val = 0.0, double x2Val = 0.0, double y2Val = 0.0);

    void read();
    void print() const;

    double getX1() const;
    void setX1(double newValue);
    double getY1() const;
    void setY1(double newValue);
    double getX2() const;
    void setX2(double newValue);
    double getY2() const;
    void setY2(double newValue);

    double length() const;

    void printPointInRatio(double lambda) const;

    bool operator==(const Segment& other) const;

    bool isParallelToOx() const;

    bool isParallelTo(const Segment& other) const;

    bool intersectsOy() const;

    bool intersectsLine(double A, double B, double C) const;

    bool containsPoint(double px, double py) const;

    double getRatioOfPoint(double px, double py) const;

    Segment operator*(double k) const;


private:
    double x1, y1;
    double x2, y2;
};
