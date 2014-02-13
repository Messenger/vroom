#include "Car.h"
#include "Angle.h"
#include "AngularVelocity.h"
#include "LinearVelocity.h"
#include "LinearAcceleration.h"
#include "Point.h"
#include "Vector.h"
#include "Time.h"

static const AngularVelocity TurningSpeed(0.2);
static const LinearAcceleration DecelerationRate(0.001);

struct Car::Impl {
    Impl()
        : Direction(90)
        , Position(320,240)
        , Speed(0)
        , MaxSpeed(0.5)
        , Acceleration(0.001)
        , UpdateDirection([] (const Time&) {})
        , UpdatePosition([] (const Time&) {})
    {
    }
    
    Angle Direction;
    Point Position;
    LinearVelocity Speed;
    LinearVelocity MaxSpeed;
    LinearAcceleration Acceleration;

    std::function<void(const Time&)> UpdateDirection;
    std::function<void(const Time&)> UpdatePosition;
};

Car::Car()
    : pImpl(new Impl())
{

}

Car::~Car() 
{
}

Car::Car(Car&& car)
    : pImpl(std::move(car.pImpl))
{
}

Angle Car::Direction() const
{
    return pImpl->Direction;
}

void Car::Direction(const Angle& direction)
{
    pImpl->Direction = direction;
}

Point Car::Position() const
{
    return pImpl->Position;
}

void Car::Position(const Point& position)
{
    pImpl->Position = position;
}

LinearVelocity Car::Speed() const
{
    return pImpl->Speed;
}

void Car::Speed(const LinearVelocity& speed)
{
    pImpl->Speed = speed;
}

LinearVelocity Car::MaxSpeed() const
{
    return pImpl->MaxSpeed;
}

void Car::MaxSpeed(const LinearVelocity& speed)
{
    pImpl->MaxSpeed = speed;
}

void Car::Update(const Time& time)
{
    pImpl->UpdateDirection(time);
    pImpl->UpdatePosition(time);
}

void Car::StartTurningLeft()
{
    pImpl->UpdateDirection = [&] (const Time& time) { pImpl->Direction += time * TurningSpeed; };
}

void Car::StartTurningRight()
{
    pImpl->UpdateDirection = [&] (const Time& time) { pImpl->Direction -= time * TurningSpeed; };
}

void Car::StopTurning()
{
    pImpl->UpdateDirection = [] (const Time& time) { };
}

void Car::StartAccelerating()
{
    pImpl->UpdatePosition = [&] (const Time& time) { 
        pImpl->Position += Vector(time * pImpl->Speed, pImpl->Direction); 
        pImpl->Speed += time * pImpl->Acceleration;
        pImpl->Speed = std::min(pImpl->Speed, pImpl->MaxSpeed);
    };
}

void Car::StopAccelerating()
{
    pImpl->UpdatePosition = [&] (const Time& time) { 
        pImpl->Position += Vector(time * pImpl->Speed, pImpl->Direction); 
        pImpl->Speed -= time * DecelerationRate;
        pImpl->Speed = std::max(pImpl->Speed, LinearVelocity(0));
    };
}
