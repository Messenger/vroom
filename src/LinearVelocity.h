#ifndef LINEAR_VELOCITY_H_
#define LINEAR_VELOCITY_H_

class Length;
class Time;

class LinearVelocity
{
    double Value;

public:
    LinearVelocity(double value);
    
    friend Length operator*(const Time& time, const LinearVelocity& speed);
    friend Length operator*(const LinearVelocity& speed, const Time& time);
};

#endif
