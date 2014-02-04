#ifndef LINEAR_VELOCITY_H_
#define LINEAR_VELOCITY_H_

class Distance;
class Time;

class LinearVelocity
{
    double Value;

public:
    LinearVelocity(double value);
    
    friend Distance operator*(const Time& time, const LinearVelocity& speed);
    friend Distance operator*(const LinearVelocity& speed, const Time& time);
};

#endif
