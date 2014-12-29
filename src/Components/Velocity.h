#ifndef COMPONENTS_VELOCITY_H_
#define COMPONENTS_VELOCITY_H_

#include "Component.h"
#include "LinearVelocity.h"

class Velocity : public Component
{
public:
    Velocity() : Value(0), Max(0) {}
    LinearVelocity Value;
    LinearVelocity Max;
};

#endif