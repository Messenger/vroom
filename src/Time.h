#ifndef TIME_H_
#define TIME_H_

class Angle;
class AngularVelocity;
class Distance;
class LinearVelocity;

class Time
{    
    int Value;
    
public:
    Time(int ms);

    friend Angle operator*(const Time& time, const AngularVelocity& speed);
    friend Angle operator*(const AngularVelocity& speed, const Time& time);
    friend Distance operator*(const Time& time, const LinearVelocity& speed);
    friend Distance operator*(const LinearVelocity& speed, const Time& time);
};

Angle operator*(const Time& time, const AngularVelocity& speed);
Angle operator*(const AngularVelocity& speed, const Time& time);
Distance operator*(const Time& time, const LinearVelocity& speed);
Distance operator*(const LinearVelocity& speed, const Time& time);

#endif