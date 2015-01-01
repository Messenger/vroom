#include "Distance.h"
#include <ostream>
#include <cmath>
#include "Ratio.h"
#include "LinearVelocity.h"
#include "Time.h"
#include "Point.h"

Distance::Distance(double value)
    : value(value)
{
}

Distance::Distance(const Point& start, const Point& end)
    : value(std::sqrt(std::pow((end.X() - start.X()).Value(), 2) 
                    + std::pow((end.Y() - start.Y()).Value(), 2)))
{

}

double Distance::Value() const
{
    return value;
}

Distance& Distance::operator+=(const Distance& distance)
{
    value += distance.value;
    return *this;
}

Distance Distance::operator-() const
{
    return -value;
}

Distance operator+(const Distance& lhs, const Distance& rhs)
{
    return Distance(lhs.Value() + rhs.Value());
}

Distance operator-(const Distance& lhs, const Distance& rhs)
{
    return Distance(lhs.Value() - rhs.Value());
}

Distance operator*(const Distance& lhs, const Distance& rhs)
{
    return Distance(lhs.Value() * rhs.Value());
}

Distance operator/(const Distance& lhs, const Distance& rhs)
{
    return lhs.Value() / rhs.Value();
}

Distance operator*(const Ratio& ratio, const Distance& distance)
{
    return Distance(ratio.Value() * distance.Value());
}

Distance operator*(const Distance& distance, const Ratio& ratio)
{
    return Distance(ratio.Value() * distance.Value());
}

Distance operator*(const Time& time, const LinearVelocity& speed)
{
    return Distance(time.Value() * speed.Value());
}

Distance operator*(const LinearVelocity& speed, const Time& time)
{
    return Distance(time.Value() * speed.Value());
}

bool operator==(const Distance& lhs, const Distance& rhs)
{
    return std::abs(lhs.Value() - rhs.Value()) < 0.0001;
}

bool operator!=(const Distance& lhs, const Distance& rhs)
{
    return std::abs(lhs.Value() - rhs.Value()) > 0.0001;
}

bool operator<(const Distance& lhs, const Distance& rhs)
{
    return lhs.Value() < rhs.Value();
}

bool operator<=(const Distance& lhs, const Distance& rhs)
{
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Distance& lhs, const Distance& rhs)
{
    return lhs.Value() > rhs.Value();
}

bool operator>=(const Distance& lhs, const Distance& rhs)
{
    return lhs > rhs || lhs == rhs;
}

std::ostream& operator<<(std::ostream& out, const Distance& distance)
{
    out << distance.Value();
    return out;
}

