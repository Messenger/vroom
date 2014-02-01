#ifndef LENGTH_H_
#define LENGTH_H_

class Point;

class Length
{
    int Value;
public:
    Length(int value);
    
    friend class Point;
    friend Point operator+(const Point&, const Length&);
    friend Point operator+(const Length&, const Point&);
};

#endif