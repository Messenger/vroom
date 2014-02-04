#include "Angle.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "Ratio.h"

Angle::Angle(double value)
    : Value(value)
{
}

Ratio Angle::Sin() const
{
    return Ratio(std::sin(M_PI * Value / 180.0));
}

Ratio Angle::Cos() const
{
    return Ratio(std::cos(M_PI * Value / 180.0));
}

Angle& Angle::operator+=(const Angle& rhs)
{
    Value += rhs.Value;
    return *this;
}

Angle& Angle::operator-=(const Angle& rhs)
{
    Value -= rhs.Value;
    return *this;
}

bool operator<(const Angle& lhs, const Angle& rhs)
{
    return lhs.Value < rhs.Value;
}

bool operator>(const Angle& lhs, const Angle& rhs)
{
    return lhs.Value > rhs.Value;
}

bool operator==(const Angle& lhs, const Angle& rhs)
{
    return lhs.Value == rhs.Value;
}
