#ifndef ANGLE_H_
#define ANGLE_H_

class Ratio;

class Angle
{
    double value;
    
public:
    Angle(double value);

    double Value() const;
    
    Ratio Sin() const;
    Ratio Cos() const;
    
    Angle& operator+=(const Angle& rhs);
    Angle& operator-=(const Angle& rhs);
};

bool operator<(const Angle& lhs, const Angle& rhs);
bool operator>(const Angle& lhs, const Angle& rhs);
bool operator==(const Angle& lhs, const Angle& rhs);

#endif