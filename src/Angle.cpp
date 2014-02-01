#include "Angle.h"

Angle::Angle(double value)
    : Value(value)
{
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
