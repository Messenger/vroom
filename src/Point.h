#ifndef POINT_H_
#define POINT_H_

#include <iosfwd>
#include "Length.h"

class Length;

class Point
{
    int X,Y;
public:
    Point(int x, int y);
    
    Point& operator+=(const Length& rhs);
    Point& operator-=(const Length& rhs);
    
    friend bool operator==(const Point& lhs, const Point& rhs);
    friend Point operator+(const Point&, const Length&);
    friend Point operator+(const Length&, const Point&);
    friend std::ostream& operator<<(std::ostream& out, const Point& point);
};

bool operator==(const Point& lhs, const Point& rhs);
Point operator+(const Point&, const Length&);
Point operator+(const Length&, const Point&);

#endif