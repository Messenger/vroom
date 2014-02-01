#include <igloo/igloo.h>
#include "Car.h"
#include "Angle.h"
#include "Time.h"
#include "Point.h"

using namespace igloo;

Context(car)
{
    Spec(should_change_direction_when_turning_left)
    {
        auto initialDirection = car.Direction();
        car.StartTurningLeft();
        car.Update(100);
        car.StopTurning();
        Assert::That(car.Direction(), Is().GreaterThan(initialDirection));
    } 

    Spec(should_change_direction_when_turning_right)
    {
        auto initialDirection = car.Direction();
        car.StartTurningRight();
        car.Update(100);
        car.StopTurning();
        Assert::That(car.Direction(), Is().LessThan(initialDirection));
    }
    
    Spec(should_move_when_accelerated)
    {
        auto position = car.Position();
        car.StartAccelerating();
        car.Update(100);
        car.StopAccelerating();
        Assert::That(car.Position(), Is().Not().EqualTo(position));
    }
    
    Car car;
};