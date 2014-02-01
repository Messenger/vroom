#ifndef POINT_H_
#define POINT_H_

class Point
{
    int X,Y;
public:
    Point(int x, int y);
    
    friend bool operator==(const Point& lhs, const Point& rhs);
};

bool operator==(const Point& lhs, const Point& rhs);

#endif