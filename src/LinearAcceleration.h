#ifndef LINEAR_ACCELERATION_H_
#define LINEAR_ACCELERATION_H_

class LinearAcceleration
{
    double value;
    
public:
    LinearAcceleration(double value);
    
    double Value() const;    
};

bool operator<(const LinearAcceleration& lhs, const LinearAcceleration& rhs);

#endif