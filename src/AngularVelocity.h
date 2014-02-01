#ifndef ANGULAR_VELOCITY_H_
#define ANGULAR_VELOCITY_H_

class Time;
class Angle;

class AngularVelocity
{
    double Value;
    
public:
    AngularVelocity(double value);
    
    friend Angle operator*(const Time& time, const AngularVelocity& speed);
    friend Angle operator*(const AngularVelocity& speed, const Time& time);
};

#endif