#ifndef VECTOR_H_
#define VECTOR_H_

#include "Distance.h"
#include "Angle.h"

class Vector
{
    Distance magnitude;
    Angle direction;

public:
    Vector(const Distance& magnitude, const Angle& direction);
    
    Distance X_Component() const;
    Distance Y_Component() const;
};

#endif