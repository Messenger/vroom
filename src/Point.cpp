#include "Point.h"
#include <ostream>
#include "Vector.h"

Point::Point(const Distance& x, const Distance& y)
    : x(x)
    , y(y)
{
}

Distance Point::X() const
{
    return x;
}

Distance Point::Y() const
{
    return y;
}

Point& Point::operator+=(const Vector& vector)
{
    x += vector.X_Component();
    y += vector.Y_Component();
    return *this;
}

Point& Point::operator+=(const Point& point)
{
    x += point.x;
    y += point.y;
    return *this;
}

Point& Point::operator-()
{
    x = -x;
    y = -y;
    return *this;
}

bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.X() == rhs.X() && lhs.Y() == rhs.Y();
}

bool operator!=(const Point& lhs, const Point& rhs)
{
    return lhs.X() != rhs.X() || lhs.Y() != rhs.Y();
}

Point operator+(const Point& lhs, const Vector& rhs)
{
    return {lhs.X() + rhs.X_Component(), lhs.Y() + rhs.Y_Component()};
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return {lhs.X() + rhs.X(), lhs.Y() + rhs.Y()};
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return {lhs.X() - rhs.X(), lhs.Y() - rhs.Y()};
}

Point operator*(const Point& point, double scalar)
{
    return {point.X() * scalar, point.Y() * scalar};
}

Point operator*(double scalar, const Point& point)
{
    return {point.X() * scalar, point.Y() * scalar};
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "(" << point.X() << "," << point.Y() << ")";
    return out;
}