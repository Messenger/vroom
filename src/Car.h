#ifndef CAR_H_
#define CAR_H_

#include <memory>

class Angle;
class Time;
class Point;
class LinearVelocity;
class Polygon;

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
    Polygon Hitbox() const;
    Point Position() const;
    void Position(const Point& point);
    LinearVelocity Speed() const;
    void Speed(const LinearVelocity& speed);
    LinearVelocity MaxSpeed() const;
    void MaxSpeed(const LinearVelocity& speed);
    
    void Update(const Time& time);
    
    void StartTurningLeft();
    void StartTurningRight();
    void StopTurning();
    
    void StartAccelerating();
    void StopAccelerating();
    
    void Collide(const Point& initial, const Point& collision, const Time& time);
};

#endif