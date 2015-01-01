#ifndef SYSTEMS_COLLISION_H_
#define SYSTEMS_COLLISION_H_

#include "System.h"

class Time;

class Collision : public System
{
public:
    void Update(const Time& time);
};

#endif