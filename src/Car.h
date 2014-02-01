#ifndef CAR_H_
#define CAR_H_

#include <memory>

class Angle;
class Time;
class Point;

class Car 
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Car();
    ~Car();
    Angle Direction();
    Point Position();
    
    void Update(const Time& time);
    
    void StartTurningLeft();
    void StartTurningRight();
    void StopTurning();
    
    void StartAccelerating();
    void StopAccelerating();
};

#endif