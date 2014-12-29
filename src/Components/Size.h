#ifndef COMPONENTS_SIZE_H_
#define COMPONENTS_SIZE_H_

#include "Component.h"
#include "Distance.h"

class Size : public Component
{
public:
    Size() : Height(0), Width(0) {}
    Distance Height;
    Distance Width;
};

#endif