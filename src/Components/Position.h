#ifndef COMPONENTS_POSITION_H_
#define COMPONENTS_POSITION_H_

#include "Point.h"
#include "Component.h"

class Position : public Component
{
public:
    Position() : Value({0, 0}) {}
    Point Value;
};

#endif