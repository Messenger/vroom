#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <memory>
#include <list>

class Point;
class Distance;
class Vector;
class Interval;

class Rectangle
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Rectangle(const Point& origin, const Distance& width, const Distance& height);
    ~Rectangle();
    
    Point LowerLeft() const;
    Point UpperLeft() const;
    Point LowerRight() const;
    Point UpperRight() const;
    
    std::list<Point> Points() const;
    std::list<Vector> Edges() const;
    Interval Project(Vector axis) const;
};

#endif