#ifndef RATIO_H_
#define RATIO_H_

class Distance;

class Ratio
{
    double value;
    
public:
    Ratio(double value);
    
    double Value() const;
};

#endif