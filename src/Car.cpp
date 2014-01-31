#include "Car.h"
#include "Direction.h"

struct Car::Impl {
    class Direction Direction;

    Impl() 
    {
    }
};

Car::Car()
    : pImpl(new Impl())
{

}

Car::~Car() 
{
}

Direction Car::Direction()
{
    return pImpl->Direction;
}

void Car::Update(int ms)
{
    pImpl->Direction.Update(ms);
}

void Car::StartTurningLeft()
{
    pImpl->Direction.Update = [&] (int ms) { pImpl->Direction.Value += ms; };
}

void Car::StartTurningRight()
{
    pImpl->Direction.Update = [&] (int ms) { pImpl->Direction.Value -= ms; };
}

void Car::StopTurning()
{
    pImpl->Direction.Update = [] (int ms) { };
}
