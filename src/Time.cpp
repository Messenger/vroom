#include "Time.h"

Time::Time(int value)
    : value(value)
{
}

int Time::Value() const
{
    return value;
}

Time operator-(const Time& lhs, const Time& rhs)
{
    return Time(lhs.Value() - rhs.Value());
}