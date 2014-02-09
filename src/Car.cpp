#include "Car.h"
#include "Angle.h"
#include "AngularVelocity.h"
#include "LinearVelocity.h"
#include "Point.h"
#include "Vector.h"
#include "Time.h"

static const AngularVelocity TurningSpeed(0.2);

struct Car::Impl {
    Impl()
        : Direction(90)
        , Position(0,0)
        , Speed(0.3)
        , UpdateDirection([] (const Time&) {})
        , UpdatePosition([] (const Time&) {})
    {
    }
    
    Angle Direction;
    Point Position;
    LinearVelocity Speed;

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

void Car::Speed(const LinearVelocity& speed)
{
    pImpl->Speed = speed;
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
    pImpl->UpdatePosition = [&] (const Time& time) { pImpl->Position += Vector(time * pImpl->Speed, pImpl->Direction); };
}

void Car::StopAccelerating()
{
    pImpl->UpdatePosition = [] (const Time& time) { };
}
