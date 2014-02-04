#include "Time.h"
#include "Angle.h"
#include "AngularVelocity.h"
#include "Distance.h"
#include "LinearVelocity.h"

Time::Time(int value)
    : Value(value)
{
}

Angle operator*(const Time& time, const AngularVelocity& speed)
{
    return Angle(time.Value * speed.Value);
}

Angle operator*(const AngularVelocity& speed, const Time& time)
{
    return Angle(time.Value * speed.Value);
}

Distance operator*(const Time& time, const LinearVelocity& speed)
{
    return Distance(time.Value * speed.Value);
}

Distance operator*(const LinearVelocity& speed, const Time& time)
{
    return Distance(time.Value * speed.Value);
}
