#ifndef LINEAR_VELOCITY_H_
#define LINEAR_VELOCITY_H_

#include <iosfwd>

class Time;
class LinearAcceleration;

class LinearVelocity
{
    double value;

public:
    LinearVelocity(double value);
    
    double Value() const;
    
    LinearVelocity& operator+=(const LinearVelocity& rhs);
    LinearVelocity& operator-=(const LinearVelocity& rhs);
    LinearVelocity& operator-();
};

bool operator<(const LinearVelocity& lhs, const LinearVelocity& rhs);
bool operator>(const LinearVelocity& lhs, const LinearVelocity& rhs);
bool operator==(const LinearVelocity& lhs, const LinearVelocity& rhs);
std::ostream& operator<<(std::ostream& out, const LinearVelocity& speed);

LinearVelocity operator*(const Time& time, const LinearAcceleration& acceleration);
LinearVelocity operator*(const LinearAcceleration& acceleration, const Time& time);

#endif
