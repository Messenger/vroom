#include "Car.h"
#include "Angle.h"
#include "AngularVelocity.h"
#include "Point.h"

static const AngularVelocity TurningSpeed(1);

struct Car::Impl {
    Impl()
        : Direction(90)
        , Position(320,240)
        , UpdateDirection([] (const Time&) {})
        , UpdatePosition([] (const Time&) {})
    {
    }
    
    Angle Direction;
    Point Position;

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

Angle Car::Direction()
{
    return pImpl->Direction;
}

Point Car::Position()
{
    return pImpl->Position;
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
    pImpl->UpdatePosition = [&] (const Time& time) { pImpl->Position = Point(1,1); };
}

void Car::StopAccelerating()
{
    pImpl->UpdatePosition = [] (const Time& time) { };
}
