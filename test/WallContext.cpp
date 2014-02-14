#include <igloo/igloo.h>
#include "World.h"
#include "Car.h"
#include "Wall.h"
#include "Point.h"
#include "Angle.h"
#include "LinearVelocity.h"
#include "Time.h"
#include "Distance.h"

using namespace igloo;

Context(wall)
{
    Spec(wall_should_prevent_car_from_travelling_through)
    {
        Wall wall(Point(-50,50), Point(50,50));
        world.Walls().push_back(std::move(wall));

        world.Cars().push_back(std::move(Car()));
        auto& car = world.Cars().front();
        car.Position(Point(0,0));
        car.Direction(90);
        car.MaxSpeed(100);
        car.Speed(100);
        car.StartAccelerating();
        world.Update(1000);
        Assert::That(car.Position().Y(), Is().LessThan(51));
    }

    Spec(wall_should_not_prevent_car_from_travelling_through_when_it_does_not_intersect)
    {
        Wall wall(Point(-100,50), Point(-1,50));
        world.Walls().push_back(std::move(wall));

        world.Cars().push_back(std::move(Car()));
        auto& car = world.Cars().front();
        car.Position(Point(0,0));
        car.Direction(90);
        car.MaxSpeed(100);
        car.Speed(100);
        car.StartAccelerating();
        world.Update(1000);
        Assert::That(car.Position().Y(), Is().GreaterThan(50));
    }
    
    World world;
};
