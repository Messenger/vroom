#ifndef VECTOR_H_
#define VECTOR_H_

#include "Distance.h"
#include "Angle.h"

class Vector
{
    Distance Magnitude;
    Angle Direction;

public:
    Vector(const Distance& magnitude, const Angle& direction);
    
    friend class Point;
};

#endif