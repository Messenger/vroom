#ifndef WORLD_H_
#define WORLD_H_

#include <memory>
#include <list>

class Car;
class Time;
class Wall;
class Point;
class Distance;

class World
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    World();
    ~World();

    Distance Height() const;
    Distance Width() const;
    Point ViewOffset() const;
    std::list<Car>& Cars() const;
    std::list<Wall>& Walls() const;
    void Update(const Time& time);
};

#endif