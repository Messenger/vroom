#ifndef COMPONENTS_SPRITE_H_
#define COMPONENTS_SPRITE_H_

#include "Component.h"
#include "Distance.h"
#include "Point.h"

class Sprite : public Component
{
public:
    Sprite() : Offset({0, 0}), Width(0), Height(0) {}
    Point Offset;
    Distance Width;
    Distance Height;
};

#endif