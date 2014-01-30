#include "Car.h"

struct Car::Impl {
    int Direction;

    Impl() 
        : Direction(0)
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

int Car::Direction()
{
    return pImpl->Direction;
}

void Car::StartTurningLeft()
{
    
}

void Car::Update(int ms)
{
    pImpl->Direction++;
}

void Car::StopTurningLeft()
{
}
