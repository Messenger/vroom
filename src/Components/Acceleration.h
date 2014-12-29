#ifndef COMPONENTS_ACCELERATION_H_
#define COMPONENTS_ACCELERATION_H_

#include "Component.h"
#include "LinearAcceleration.h"
#include "LinearVelocity.h"

class Acceleration : public Component
{
public:
    Acceleration() : Value(0) {}
    LinearAcceleration Value;
};

#endif