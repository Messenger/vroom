#include "Point.h"
#include <ostream>
#include "Vector.h"
#include "Ratio.h"

Point::Point(const Distance& x, const Distance& y)
    : X(x)
    , Y(y)
{
}

Point& Point::operator+=(const Vector& vector)
{
    X += vector.Magnitude * vector.Direction.Cos();
    Y += vector.Magnitude * vector.Direction.Sin();
    return *this;
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y;
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return Point(lhs.X + rhs.X, lhs.Y + rhs.Y);
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "(" << point.X << "," << point.Y << ")";
    return out;
}