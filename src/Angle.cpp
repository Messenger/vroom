#include "Angle.h"
#include <cmath>
#include "Ratio.h"
#include "Time.h"
#include "AngularVelocity.h"

static constexpr double pi() { return std::atan(1)*4; }

Angle::Angle(double value)
    : value(value)
{
}

Angle Angle::Radians(double value)
{
    return Angle(value * 180.0 / pi());
}

double Angle::Value() const
{
    return value;
}

Ratio Angle::Sin() const
{
    return Ratio(std::sin(pi() * value / 180.0));
}

Ratio Angle::Cos() const
{
    return Ratio(std::cos(pi() * value / 180.0));
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
    return std::abs(lhs.Value() - rhs.Value()) < 0.0001;
}

Angle operator*(const Time& time, const AngularVelocity& speed)
{
    return Angle(time.Value() * speed.Value());
}

Angle operator*(const AngularVelocity& speed, const Time& time)
{
    return Angle(time.Value() * speed.Value());
}