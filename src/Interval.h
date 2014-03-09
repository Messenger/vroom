#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "Distance.h"

class Interval
{
    Distance Minimum;
    Distance Maximum;
    
public:
    Interval(const Distance& min, const Distance& max);
    
    bool Overlaps(const Interval& value) const;
};

#endif