#ifndef POINT_H_
#define POINT_H_

#include <iosfwd>

#include "Distance.h"

class Vector;

class Point
{
    Distance x,y;
public:
    Point(const Distance& x, const Distance& y);
    
    Distance X() const;
    Distance Y() const;

    Point& operator+=(const Vector& vector);
    Point& operator+=(const Point& point);
    Point operator-() const;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Vector& rhs);
Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& lhs, double rhs);
Point operator*(double lhs, const Point& rhs);
std::ostream& operator<<(std::ostream& out, const Point& point);

#endif