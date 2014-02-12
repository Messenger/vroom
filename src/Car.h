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
    Car(Car&& car);
    
    Angle Direction() const;
    void Direction(const Angle& angle);
    Point Position() const;
    void Speed(const LinearVelocity& speed);
    LinearVelocity Speed() const;
    void MaxSpeed(const LinearVelocity& speed);
    LinearVelocity MaxSpeed() const;
    
    void Update(const Time& time);
    
    void StartTurningLeft();
    void StartTurningRight();
    void StopTurning();
    
    void StartAccelerating();
    void StopAccelerating();
};

#endif