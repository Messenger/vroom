#include "Interval.h"

Interval::Interval(const Distance& min, const Distance& max)
    : Minimum(min)
    , Maximum(max)
{

}

bool Interval::Overlaps(const Interval& value) const
{
    return DistanceTo(value) <= 0;
}

Distance Interval::DistanceTo(const Interval& value) const
{
    return Minimum < value.Minimum ? value.Minimum - Maximum
                                   : Minimum - value.Maximum;
}


Interval& Interval::operator+=(const Distance& value)
{ 
    if(value < 0)
    {
        Minimum += value;
    } 
    else 
    {
        Maximum += value;
    }
    return *this;
}

Interval operator+(const Interval& interval, const Distance& distance)
{
    Interval value(interval);
    return value += distance;
}