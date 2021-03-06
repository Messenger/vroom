#ifndef ANGLE_H_
#define ANGLE_H_

class Ratio;
class Time;
class AngularVelocity;

class Angle
{
    double value;
    
public:
    Angle(double value);
    static Angle Radians(double value);

    double Value() const;
    
    Ratio Sin() const;
    Ratio Cos() const;
    
    Angle& operator+=(const Angle& rhs);
    Angle& operator-=(const Angle& rhs);
    
    static Angle East();
    static Angle North();
    static Angle West();
    static Angle South();
};

bool operator<(const Angle& lhs, const Angle& rhs);
bool operator>(const Angle& lhs, const Angle& rhs);
bool operator==(const Angle& lhs, const Angle& rhs);
Angle operator+(const Angle& lhs, const Angle& rhs);
Angle operator-(const Angle& lhs, const Angle& rhs);
Angle operator*(const Time& time, const AngularVelocity& speed);
Angle operator*(const AngularVelocity& speed, const Time& time);

#endif