#include "LinearVelocity.h"
#include <ostream>
#include <cmath>
#include "Time.h"
#include "LinearAcceleration.h"

LinearVelocity::LinearVelocity(double value)
    : value(value)
{
}

double LinearVelocity::Value() const
{
    return value;
}

LinearVelocity& LinearVelocity::operator+=(const LinearVelocity& rhs)
{
    value += rhs.value;
    return *this;
}

LinearVelocity& LinearVelocity::operator-=(const LinearVelocity& rhs)
{
    value -= rhs.value;
    return *this;
}

bool operator<(const LinearVelocity& lhs, const LinearVelocity& rhs)
{
    return lhs.Value() < rhs.Value();
}

bool operator>(const LinearVelocity& lhs, const LinearVelocity& rhs)
{
    return lhs.Value() > rhs.Value();
}

bool operator==(const LinearVelocity& lhs, const LinearVelocity& rhs)
{
    return std::abs(lhs.Value() - rhs.Value()) < 0.0001;
}

std::ostream& operator<<(std::ostream& out, const LinearVelocity& speed)
{
    out << speed.Value();
    return out;
}

LinearVelocity operator*(const Time& time, const LinearAcceleration& acceleration)
{
    return LinearVelocity(time.Value() * acceleration.Value());
}

LinearVelocity operator*(const LinearAcceleration& acceleration, const Time& time)
{
    return LinearVelocity(time.Value() * acceleration.Value());
}
