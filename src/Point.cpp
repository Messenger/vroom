#include "Point.h"

Point::Point(int x, int y)
    : X(x)
    , Y(y)
{
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y;
}