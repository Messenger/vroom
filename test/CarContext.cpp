#include <igloo/igloo.h>
#include "Car.h"
#include "Direction.h"

using namespace igloo;

Context(car)
{
    Spec(should_change_direction_when_turning_left)
    {
        auto initialDirection = car.Direction().Value;
        car.StartTurningLeft();
        car.Update(100);
        car.StopTurning();
        Assert::That(car.Direction().Value, Is().GreaterThan(initialDirection));
    } 

    Spec(should_change_direction_when_turning_right)
    {
        auto initialDirection = car.Direction().Value;
        car.StartTurningRight();
        car.Update(100);
        car.StopTurning();
        Assert::That(car.Direction().Value, Is().LessThan(initialDirection));
    }
    
    Car car;
};