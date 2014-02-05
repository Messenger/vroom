#include "Distance.h"
#include <ostream>
#include "Ratio.h"

Distance::Distance(int value)
    : value(value)
{
}

int Distance::Value() const
{
    return value;
}

Distance& Distance::operator+=(const Distance& distance)
{
    value += distance.value;
    return *this;
}

Distance operator+(const Distance& lhs, const Distance& rhs)
{
    return Distance(lhs.Value() + rhs.Value());
}

Distance operator*(const Ratio& ratio, const Distance& distance)
{
    return Distance(ratio.Value() * distance.Value());
}

Distance operator*(const Distance& distance, const Ratio& ratio)
{
    return Distance(ratio.Value() * distance.Value());
}

bool operator==(const Distance& lhs, const Distance& rhs)
{
    return lhs.Value() == rhs.Value();
}

std::ostream& operator<<(std::ostream& out, const Distance& distance)
{
    out << distance.Value();
    return out;
}

