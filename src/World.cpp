#include "World.h"
#include <list>
#include <algorithm>
#include "Car.h"
#include "Wall.h"
#include "Point.h"

struct World::Impl
{
    std::list<Car> Cars;
    std::list<Wall> Walls;
};

World::World()
    : pImpl(new Impl)
{
}

World::~World()
{
}

std::list<Car>& World::Cars() const
{
    return pImpl->Cars;
}

std::list<Wall>& World::Walls() const
{
    return pImpl->Walls;
}

void World::Update(const Time& time)
{
    std::for_each(pImpl->Cars.begin(), pImpl->Cars.end(),
        [&] (Car& car) { 
            auto initialPosition = car.Position();
            car.Update(time);
            auto finalPosition = car.Position();
            std::for_each(pImpl->Walls.begin(), pImpl->Walls.end(),
                [&] (const Wall& wall) {
                    Point collision(0,0);
                    if(wall.Intersects(initialPosition, finalPosition, collision))
                    {
                        car.Position(collision);
                        finalPosition = collision;
                    }
                });
        });
}
