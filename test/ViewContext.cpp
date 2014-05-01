#include <igloo/igloo.h>
#include "World.h"
#include "Car.h"
#include "Angle.h"
#include "Time.h"
#include "Point.h"
#include "LinearVelocity.h"

using namespace igloo;

Context(view)
{
    Car& CreateReallyFastCar()
    {
        world.Cars().push_back(std::move(Car()));
        auto& car = world.Cars().back();
        car.Position(Point {20,20});
        car.MaxSpeed(100);
        car.Speed(100);
        return car;
    }

    Spec(view_should_follow_the_car_vertically)
    {
        auto& car = CreateReallyFastCar();
        car.Direction(Angle::North());
        car.StartAccelerating();
        world.Update(100);
        Assert::That(world.ViewOffset().Y(), Is().GreaterThan(0));
    }

    Spec(view_should_follow_the_car_horizontally)
    {
        auto& car = CreateReallyFastCar();
        car.Direction(Angle::East());
        car.StartAccelerating();
        world.Update(100);
        Assert::That(world.ViewOffset().X(), Is().GreaterThan(0));
    }

    Spec(view_should_follow_the_car_negatively_vertical)
    {
        auto& car = CreateReallyFastCar();
        car.Direction(Angle::South());
        car.StartAccelerating();
        world.Update(100);
        Assert::That(world.ViewOffset().Y(), Is().LessThan(0));
    }

    Spec(view_should_follow_the_car_negatively_horizontal)
    {
        auto& car = CreateReallyFastCar();
        car.Direction(Angle::West());
        car.StartAccelerating();
        world.Update(100);
        Assert::That(world.ViewOffset().X(), Is().LessThan(0));
    }

    Spec(view_should_not_move_if_the_car_does_not_leave_the_screen)
    {
        auto initial = world.ViewOffset();
        auto& car = CreateReallyFastCar();
        car.Position( {200, 200});
        car.Direction(Angle::East());
        car.Speed(1);
        car.MaxSpeed(1);
        car.StartAccelerating();
        world.Update(100);
        Assert::That(initial, Is().EqualTo(world.ViewOffset()));
    }

    World world;
};
