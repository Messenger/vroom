#ifndef COMPONENTS_ROTATION_H_
#define COMPONENTS_ROTATION_H_

#include "Component.h"
#include "AngularVelocity.h"

class Rotation : public Component
{
public:
    Rotation() : Value(0) { }
    AngularVelocity Value;
};

#endif