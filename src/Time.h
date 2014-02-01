#ifndef TIME_H_
#define TIME_H_

class Angle;
class AngularVelocity;
class Length;
class LinearVelocity;

class Time
{    
    int Value;
    
public:
    Time(int ms);

    friend Angle operator*(const Time& time, const AngularVelocity& speed);
    friend Angle operator*(const AngularVelocity& speed, const Time& time);
    friend Length operator*(const Time& time, const LinearVelocity& speed);
    friend Length operator*(const LinearVelocity& speed, const Time& time);
};

Angle operator*(const Time& time, const AngularVelocity& speed);
Angle operator*(const AngularVelocity& speed, const Time& time);
Length operator*(const Time& time, const LinearVelocity& speed);
Length operator*(const LinearVelocity& speed, const Time& time);

#endif