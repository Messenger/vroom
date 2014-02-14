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

Point operator+(const Point& lhs, const Point& rhs)
{
    return Point(lhs.X() + rhs.X(), lhs.Y() + rhs.Y());
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return Point(lhs.X() - rhs.X(), lhs.Y() - rhs.Y());
}

Point operator*(const Point& point, double scalar)
{
    return Point(point.X() * scalar, point.Y() * scalar);
}

Point operator*(double scalar, const Point& point)
{
    return Point(point.X() * scalar, point.Y() * scalar);
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
    out << "(" << point.X() << "," << point.Y() << ")";
    return out;
}