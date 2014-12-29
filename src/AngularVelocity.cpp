#include "AngularVelocity.h"

AngularVelocity::AngularVelocity(double value)
    : value(value)
{
}

double AngularVelocity::Value() const
{
    return value;
}

AngularVelocity AngularVelocity::operator-() const
{
    return -value;
}
