#ifndef TIME_H_
#define TIME_H_

class Angle;
class AngularVelocity;
class Distance;
class LinearVelocity;

class Time
{    
    int value;
    
public:
    Time(int ms);
    
    int Value() const;
};

Time operator-(const Time& lhs, const Time& rhs);
Angle operator*(const Time& time, const AngularVelocity& speed);
Angle operator*(const AngularVelocity& speed, const Time& time);
Distance operator*(const Time& time, const LinearVelocity& speed);
Distance operator*(const LinearVelocity& speed, const Time& time);

#endif