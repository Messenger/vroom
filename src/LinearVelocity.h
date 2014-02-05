#ifndef LINEAR_VELOCITY_H_
#define LINEAR_VELOCITY_H_

class Distance;
class Time;

class LinearVelocity
{
    double value;

public:
    LinearVelocity(double value);
    
    double Value() const;
};

#endif
