#include <igloo/igloo.h>
#include "Car.h"
#include "Angle.h"
#include "Time.h"
#include "Point.h"
#include "LinearVelocity.h"

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
        auto initialPosition = car.Position();
        car.StartAccelerating();
        car.Update(100);
        car.Update(100);
        car.StopAccelerating();
        Assert::That(car.Position(), Is().Not().EqualTo(initialPosition));
    }
    
    Spec(should_move_to_the_east_when_accelerated_and_point_east)
    {
        auto initialPosition = car.Position();
        car.Direction(0);
        car.Speed(1);
        car.MaxSpeed(1);
        car.StartAccelerating();
        car.Update(100);
        car.StopAccelerating();
        Assert::That(car.Position(), Is().EqualTo(initialPosition + Point{100, 0}));
    }
    
    Spec(should_move_to_the_north_when_accelerated_and_pointing_north)
    {
        auto initialPosition = car.Position();
        car.Direction(90);
        car.Speed(1);
        car.MaxSpeed(1);
        car.StartAccelerating();
        car.Update(100);
        car.StopAccelerating();
        Assert::That(car.Position(), Is().EqualTo(initialPosition + Point{0, 100}));
    }

    Spec(should_accelerate_over_time)
    {
        car.StartAccelerating();
        car.Update(100);
        auto initialSpeed = car.Speed();
        car.Update(100);
        car.StopAccelerating();
        Assert::That(car.Speed(), Is().GreaterThan(initialSpeed));
    }
    
    Spec(should_not_exceed_max_speed)
    {
        car.MaxSpeed(10);
        car.StartAccelerating();
        car.Update(1000000);
        car.StopAccelerating();
        Assert::That(car.Speed(), Is().EqualTo(car.MaxSpeed()));
    }
    
    Spec(should_decelerate_while_not_accelerating)
    {
        car.MaxSpeed(10);
        car.StartAccelerating();
        car.Update(1000000);
        auto initialSpeed = car.Speed();
        car.StopAccelerating();
        car.Update(1000000);
        Assert::That(car.Speed(), Is().LessThan(initialSpeed));
    }
    
    Spec(should_not_decelerate_lower_than_zero)
    {
        car.StopAccelerating();
        car.Update(1000000);
        Assert::That(car.Speed(), Is().EqualTo(0));
    }
    
    Car car;
};