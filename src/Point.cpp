#include "Point.h"
#include "Length.h"
#include <ostream>

Point::Point(int x, int y)
    : X(x)
    , Y(y)
{
}

Point& Point::operator+=(const Length& rhs)
{
    X += rhs.Value;
    return *this;
}

Point& Point::operator-=(const Length& rhs)
{
    X -= rhs.Value;
    return *this;
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y;
}

Point operator+(const Point& point, const Length& length)
{
    return Point(point.X + length.Value, point.Y);
}

Point operator+(const Length& length, const Point& point)
{
    return Point(point.X + length.Value, point.Y);
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    return out << "(" << point.X << "," << point.Y << ")";
}