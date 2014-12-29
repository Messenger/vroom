#ifndef SYSTEMS_DEBUG_H_
#define SYSTEMS_DEBUG_H_

#include "System.h"

class Debug : public System
{
public:
    void Update(const Time& time);
};

#endif