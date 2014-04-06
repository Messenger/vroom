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
    
    Angle Direction() const;
    Distance Magnitude() const;
    Distance X_Component() const;
    Distance Y_Component() const;
    Vector Normal() const;
    Vector Normalize() const;
    Distance DotProduct(const Point& point) const;

    Vector& operator-();
};

Vector operator*(const Vector& vector, const Distance& distance);

#endif