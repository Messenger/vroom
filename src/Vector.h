#ifndef VECTOR_H_
#define VECTOR_H_

#include "Distance.h"
#include "Angle.h"

class Point;

class Vector
{
    Distance magnitude;
    Angle direction;

public:
    Vector(const Distance& magnitude, const Angle& direction);
    Vector(const Point& point);
    
    Distance X_Component() const;
    Distance Y_Component() const;
    Vector Normal() const;
    Vector Normalize() const;
    Distance DotProduct(const Point& point) const;
};

#endif