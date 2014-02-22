#include "World.h"
#include <list>
#include "Car.h"
#include "Wall.h"
#include "Point.h"
#include "ViewPort.h"

struct World::Impl
{
    std::list<Car> Cars;
    std::list<Wall> Walls;
    ViewPort View;
};

World::World()
    : pImpl(new Impl)
{
}

World::~World()
{
}

Distance World::Height() const
{
    return pImpl->View.Height();
}

Distance World::Width() const
{
    return pImpl->View.Width();
}

Point World::ViewOffset() const
{
    return pImpl->View.Offset();
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
    for(auto& car : pImpl->Cars)
    {
        auto initialPosition = car.Position();
        car.Update(time);
        auto finalPosition = car.Position();
        for(const auto& wall:  pImpl->Walls)
        {
            Point collision(0,0);
            if(wall.Intersects(initialPosition, finalPosition, collision))
            {
                finalPosition = collision;
            }
        }

        if(finalPosition != car.Position())
        {
            car.Collide(initialPosition, finalPosition, time);
        }
        
        pImpl->View.Update(car);
   }
}
