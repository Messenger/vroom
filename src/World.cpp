#include "World.h"
#include <list>
#include "Car.h"
#include "Wall.h"
#include "Point.h"

struct World::Impl
{
    std::list<Car> Cars;
    std::list<Wall> Walls;
    Distance Height {480};
    Distance Width {640};
    Point ViewOffset {0,0};
    Distance MinimumScreenDistance {80};
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
    return pImpl->Height;
}

Distance World::Width() const
{
    return pImpl->Width;
}

Point World::ViewOffset() const
{
    return pImpl->ViewOffset;
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
        
        
        if(finalPosition.Y() > pImpl->ViewOffset.Y() + pImpl->Height - pImpl->MinimumScreenDistance)
        {
            pImpl->ViewOffset += Point{0, finalPosition.Y() - (pImpl->ViewOffset.Y() + pImpl->Height - pImpl->MinimumScreenDistance)};
        }
        
        if(finalPosition.Y() < pImpl->ViewOffset.Y() + pImpl->MinimumScreenDistance)
        {
            pImpl->ViewOffset += Point{0, finalPosition.Y() - (pImpl->ViewOffset.Y() + pImpl->MinimumScreenDistance)};
        }
        
        if(finalPosition.X() > pImpl->ViewOffset.X() + pImpl->Width - pImpl->MinimumScreenDistance)
        {
            pImpl->ViewOffset += Point{finalPosition.X() - (pImpl->ViewOffset.X() + pImpl->Width - pImpl->MinimumScreenDistance), 0};
        }

        if(finalPosition.X() < pImpl->ViewOffset.X() + pImpl->MinimumScreenDistance)
        {
            pImpl->ViewOffset += Point{finalPosition.X() - (pImpl->ViewOffset.X() + pImpl->MinimumScreenDistance), 0};
        }
   }
}
