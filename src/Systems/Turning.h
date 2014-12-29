#ifndef SYSTEMS_TURNING_H_
#define SYSTEMS_TURNING_H_

#include "System.h"

class Time;

class Turning : public System
{
public:
    void Update(const Time& time);
};

#endif