#include "Vector.h"
#include "Ratio.h"

Vector::Vector(const Distance& magnitude, const Angle& direction)
    : magnitude(magnitude)
    , direction(direction)
{
}

Distance Vector::X_Component() const
{
    return magnitude * direction.Cos();
}

Distance Vector::Y_Component() const
{
    return magnitude * direction.Sin();
}
