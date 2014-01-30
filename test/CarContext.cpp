#include <igloo/igloo.h>
#include "Car.h"

using namespace igloo;

Context(car)
{
    Spec(should_change_direction_when_turning_left)
    {
        auto initialDirection = car.Direction();
        car.StartTurningLeft();
        car.Update(100);
        car.StopTurningLeft();
        Assert::That(car.Direction(), Is().GreaterThan(initialDirection));
    } 

    Car car;
};