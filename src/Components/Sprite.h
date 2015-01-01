#ifndef COMPONENTS_SPRITE_H_
#define COMPONENTS_SPRITE_H_

#include "Component.h"
#include "Distance.h"
#include "Point.h"
#include "Angle.h"

class Sprite : public Component
{
public:
    Sprite() : Direction(0), Offset({0, 0}), Width(0), Height(0) {}
    Angle Direction;
    Point Offset;
    Distance Width;
    Distance Height;
};

#endif