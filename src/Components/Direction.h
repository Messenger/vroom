#ifndef COMPONENTS_DIRECTION_H_
#define COMPONENTS_DIRECTION_H_

#include "Component.h"
#include "Angle.h"

class Direction : public Component
{
public:
    Direction() : Value(0) {}
    Angle Value;
};

#endif