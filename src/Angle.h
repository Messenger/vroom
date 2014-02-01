#ifndef ANGLE_H_
#define ANGLE_H_

class Angle
{
    double Value;
    
public:
    Angle(double value);

    Angle& operator+=(const Angle& rhs);
    Angle& operator-=(const Angle& rhs);
    
    friend bool operator<(const Angle& lhs, const Angle& rhs);
    friend bool operator>(const Angle& lhs, const Angle& rhs);
    friend bool operator==(const Angle& lhs, const Angle& rhs);
};

bool operator<(const Angle& lhs, const Angle& rhs);
bool operator>(const Angle& lhs, const Angle& rhs);
bool operator==(const Angle& lhs, const Angle& rhs);

#endif