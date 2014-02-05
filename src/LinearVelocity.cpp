#include "LinearVelocity.h"

LinearVelocity::LinearVelocity(double value)
    : value(value)
{
}

double LinearVelocity::Value() const
{
    return value;
}