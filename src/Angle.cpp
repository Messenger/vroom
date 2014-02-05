#include "Angle.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "Ratio.h"

Angle::Angle(double value)
    : value(value)
{
}

double Angle::Value() const
{
    return value;
}

Ratio Angle::Sin() const
{
    return Ratio(std::sin(M_PI * value / 180.0));
}

Ratio Angle::Cos() const
{
    return Ratio(std::cos(M_PI * value / 180.0));
}

Angle& Angle::operator+=(const Angle& rhs)
{
    value += rhs.value;
    return *this;
}

Angle& Angle::operator-=(const Angle& rhs)
{
    value -= rhs.value;
    return *this;
}

bool operator<(const Angle& lhs, const Angle& rhs)
{
    return lhs.Value() < rhs.Value();
}

bool operator>(const Angle& lhs, const Angle& rhs)
{
    return lhs.Value() > rhs.Value();
}

bool operator==(const Angle& lhs, const Angle& rhs)
{
    return lhs.Value() == rhs.Value();
}
