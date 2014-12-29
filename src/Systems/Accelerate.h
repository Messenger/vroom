#ifndef SYSTEMS_ACCELERATE_H_
#define SYSTEMS_ACCELERATE_H_

#include "System.h"

class Accelerate : public System
{
public:
    void Update(const Time& time);
};

#endif