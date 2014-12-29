#ifndef COMPONENTS_STATS_H_
#define COMPONENTS_STATS_H_

#include "Component.h"
#include "LinearAcceleration.h"
#include "AngularVelocity.h"

class Stats : public Component
{
public:
    Stats() : AccelerationRate(0), DecelerationRate(0), TurningRate(0) {}
    LinearAcceleration AccelerationRate;
    LinearAcceleration DecelerationRate;
    AngularVelocity TurningRate;
};

#endif