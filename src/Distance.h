#ifndef DISTANCE_H_
#define DISTANCE_H_

#include <iosfwd>

class Ratio;

class Distance
{
    int Value;

public:
    Distance(int value);
    
    Distance& operator+=(const Distance& distance);
    
    friend Distance operator+(const Distance& lhs, const Distance& rhs);
    friend Distance operator*(const Ratio& ratio, const Distance& distance);
    friend Distance operator*(const Distance& distance, const Ratio& ratio);
    friend bool operator==(const Distance& lhs, const Distance& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Distance& distance);
};

Distance operator+(const Distance& lhs, const Distance& rhs);
Distance operator*(const Ratio& ratio, const Distance& distance);
Distance operator*(const Distance& distance, const Ratio& ratio);
bool operator==(const Distance& lhs, const Distance& rhs);
std::ostream& operator<<(std::ostream& out, const Distance& distance);

#endif