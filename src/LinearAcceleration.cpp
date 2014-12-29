#include "LinearAcceleration.h"

LinearAcceleration::LinearAcceleration(double value)
    : value(value)
{

}

double LinearAcceleration::Value() const
{
    return value;
}

bool operator<(const LinearAcceleration& lhs, const LinearAcceleration& rhs)
{
    return lhs.Value() < rhs.Value();
}
