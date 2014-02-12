#ifndef TIME_H_
#define TIME_H_

class Time
{    
    int value;
    
public:
    Time(int ms);
    
    int Value() const;
};

Time operator-(const Time& lhs, const Time& rhs);

#endif