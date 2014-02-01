#include "Time.h"
#include "Angle.h"
#include "AngularVelocity.h"
#include "Length.h"
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

Length operator*(const Time& time, const LinearVelocity& speed)
{
    return Length(time.Value * speed.Value);
}

Length operator*(const LinearVelocity& speed, const Time& time)
{
    return Length(time.Value * speed.Value);
}
