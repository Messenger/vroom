#ifndef RATIO_H_
#define RATIO_H_

class Distance;

class Ratio
{
    double Value;
    
public:
    Ratio(double value);
    
    friend Distance operator*(const Ratio& ratio, const Distance& distance);
    friend Distance operator*(const Distance& distance, const Ratio& ratio);
};

#endif