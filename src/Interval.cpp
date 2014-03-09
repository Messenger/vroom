#include "Interval.h"

Interval::Interval(const Distance& min, const Distance& max)
    : Minimum(min)
    , Maximum(max)
{

}

bool Interval::Overlaps(const Interval& value) const
{
    auto distanceBetweenIntervals = Minimum < value.Minimum ? value.Minimum - Maximum 
                                                            : Minimum - value.Maximum;
    return distanceBetweenIntervals <= 0;
}
