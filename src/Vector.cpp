#include "Vector.h"
#include <cmath>
#include "Ratio.h"
#include "Point.h"

Vector::Vector(const Distance& magnitude, const Angle& direction)
    : magnitude{magnitude}
    , direction{direction}
{
}

Vector::Vector(const Point& point)
    : magnitude{{0,0}, point}
    , direction{Angle::Radians(std::atan((point.Y()/point.X()).Value()))}
{
}

Angle Vector::Direction() const
{
    return direction;
}

Distance Vector::Magnitude() const
{
    return magnitude;
}

Distance Vector::X_Component() const
{
    return magnitude * direction.Cos();
}

Distance Vector::Y_Component() const
{
    return magnitude * direction.Sin();
}

Vector Vector::Normal() const
{
    return Point{-Y_Component(), X_Component()};
}

Vector Vector::Normalize() const
{
    return { 1, direction};
}

Distance Vector::DotProduct(const Point& point) const
{
    return X_Component() * point.X() + Y_Component() * point.Y();
}

Vector& Vector::operator-()
{
    magnitude = -magnitude;
    return *this;
}

Vector operator*(const Vector& vector, const Distance& distance)
{
    return { vector.Magnitude() * distance, vector.Direction() };
}

