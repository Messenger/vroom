#ifndef CAR_H_
#define CAR_H_

#include <memory>

class Angle;
class Time;
class Point;
class LinearVelocity;

class Car 
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Car();
    ~Car();
    Angle Direction();
    void Direction(const Angle& angle);
    Point Position();
    void Speed(const LinearVelocity& speed);
    
    void Update(const Time& time);
    
    void StartTurningLeft();
    void StartTurningRight();
    void StopTurning();
    
    void StartAccelerating();
    void StopAccelerating();
};

#endif