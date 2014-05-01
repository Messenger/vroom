#include "Car.h"
#include <cmath>
#include "Angle.h"
#include "AngularVelocity.h"
#include "LinearVelocity.h"
#include "LinearAcceleration.h"
#include "Point.h"
#include "Vector.h"
#include "Time.h"
#include "Polygon.h"

static const AngularVelocity TurningSpeed(0.25);
static const LinearAcceleration DecelerationRate(0.001);

struct Car::Impl {
    Angle Direction {90};
    Point Position {20, 20};
    LinearVelocity Speed {0};
    LinearVelocity MaxSpeed {0.5};
    LinearAcceleration Acceleration {0.001};

    std::function<void(const Time&)> UpdateDirection {[] (const Time&) {}};
    std::function<void(const Time&)> UpdatePosition {[] (const Time&) {}};
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

Polygon Car::Hitbox() const
{
    return Polygon({
        pImpl->Position + Vector{ 20, pImpl->Direction} + Vector{ 20, pImpl->Direction + 90},
        pImpl->Position + Vector{ 20, pImpl->Direction + 90} + Vector{ 20, pImpl->Direction + 180},
        pImpl->Position + Vector{ 20, pImpl->Direction + 180} + Vector{ 20, pImpl->Direction + 270},
        pImpl->Position + Vector{ 20, pImpl->Direction + 270} + Vector{ 20, pImpl->Direction},
    });
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
    pImpl->Speed = std::min(pImpl->Speed, speed);
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
        if(pImpl->Speed > 0){
            pImpl->Speed -= time * DecelerationRate;
            pImpl->Speed = std::max(pImpl->Speed, LinearVelocity(0));
        } else {
            pImpl->Speed += time * DecelerationRate;
            pImpl->Speed = std::min(pImpl->Speed, LinearVelocity(0));
        }
    };
}

void Car::Collide(const Point& initial, const Point& collision, const Time& time)
{
    if(pImpl->Speed < 0)
    {
        return;
    }

    auto collisionToCurrent = Distance(collision, pImpl->Position);
    auto initialToCurrent = Distance(initial, pImpl->Position);
    
    auto remainingTime = time.Value() * collisionToCurrent.Value() / initialToCurrent.Value();
    
    pImpl->Position = collision;
    pImpl->Speed = -pImpl->Speed;
    pImpl->UpdatePosition(remainingTime);
}

