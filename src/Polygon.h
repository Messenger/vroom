#ifndef POLYGON_H_
#define POLYGON_H_

#include <memory>
#include <list>

class Point;
class Distance;
class Vector;
class Interval;

class Polygon
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Polygon(std::list<Point> points);
    Polygon(Polygon&& polygon);
    static Polygon Rectangle(const Point& origin, const Distance& width, const Distance& height);
    ~Polygon();
    
    Point Center() const;
    std::list<Point> Points() const;
    std::list<Vector> Edges() const;
    Interval Project(Vector axis) const;
};

#endif