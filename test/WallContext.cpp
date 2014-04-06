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
    Car& CreateReallyFastCar()
    {
        world.Cars().push_back(std::move(Car()));
        auto& car = world.Cars().back();
        car.Position({0,0});
        car.Direction(90);
        car.MaxSpeed(100);
        car.Speed(100);
        return car;
    }
    
    Wall& CreateWall(const Point& start, const Point& end)
    {
        Wall wall(start, end);
        world.Walls().push_back(std::move(wall));
        return world.Walls().back();
    }
    
    Spec(wall_should_prevent_car_from_travelling_through)
    {
        CreateWall({-50,50}, {50,50});

        auto& car = CreateReallyFastCar();
        car.MaxSpeed(51);
        car.StartAccelerating();
        world.Update(1);
        Assert::That(car.Position().Y(), Is().LessThan(51));
    }

    Spec(wall_should_not_prevent_car_from_travelling_through_when_it_does_not_intersect)
    {
        CreateWall({-100,50}, {-1,50});

        auto& car = CreateReallyFastCar();
        car.StartAccelerating();
        world.Update(1000);
        Assert::That(car.Position().Y(), Is().GreaterThan(50));
    }
    
    Spec(car_should_collide_with_nearest_wall)
    {
        CreateWall({-50,25}, {50,25});
        CreateWall({-50,50}, {50,50});

        auto& car = CreateReallyFastCar();
        car.MaxSpeed(26);
        car.StartAccelerating();
        world.Update(1);
        Assert::That(car.Position().Y(), Is().LessThan(26));
    }

    Spec(car_should_not_go_through_a_wall_if_it_lands_on_top_of_it)
    {
        CreateWall({-50,1}, {50,1});

        auto& car = CreateReallyFastCar();
        car.MaxSpeed(0.5);
        car.StartAccelerating();
        for(int i = 0; i < 79; ++i)
        {
            world.Update(13);
        }
        Assert::That(car.Position().Y(), Is().LessThan(2));
    }
    
    World world;
};
