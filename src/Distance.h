#ifndef DISTANCE_H_
#define DISTANCE_H_

#include <iosfwd>

class Ratio;
class Time;
class LinearVelocity;

class Distance
{
    int value;

public:
    Distance(int value);
    
    int Value() const;
    
    Distance& operator+=(const Distance& distance);
};

Distance operator+(const Distance& lhs, const Distance& rhs);
Distance operator*(const Ratio& ratio, const Distance& distance);
Distance operator*(const Distance& distance, const Ratio& ratio);
Distance operator*(const Time& time, const LinearVelocity& speed);
Distance operator*(const LinearVelocity& speed, const Time& time);
bool operator==(const Distance& lhs, const Distance& rhs);
std::ostream& operator<<(std::ostream& out, const Distance& distance);

#endif