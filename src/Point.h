#ifndef POINT_H_
#define POINT_H_

#include <iosfwd>

#include "Distance.h"

class Vector;

class Point
{
    Distance X,Y;
public:
    Point(const Distance& x, const Distance& y);

    Point& operator+=(const Vector& vector);
    
    friend bool operator==(const Point& lhs, const Point& rhs);
    friend Point operator+(const Point& lhs, const Point& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

bool operator==(const Point& lhs, const Point& rhs);
Point operator+(const Point& lhs, const Point& rhs);
std::ostream& operator<<(std::ostream& out, const Point& point);

#endif