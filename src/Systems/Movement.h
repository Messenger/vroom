#ifndef SYSTEMS_MOVEMENT_H_
#define SYSTEMS_MOVEMENT_H_

#include "System.h"

class Movement : public System
{
public:
    void Update(const Time& time);
};

#endif