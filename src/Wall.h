#ifndef WALL_H_
#define WALL_H_

#include <memory>

class Point;
class Distance;
class Angle;
class Polygon;

class Wall
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Wall(const Point& start, const Point& end);
    ~Wall();
    Wall(Wall&& wall);
    
    Point Start() const;
    Polygon Hitbox() const;
    Angle Direction() const;
    Distance Length() const;
    bool Intersects(const Point& start, const Point& end, Point& collision) const;
};

#endif