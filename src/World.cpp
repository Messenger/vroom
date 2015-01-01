#include "World.h"
#include <list>
#include "Car.h"
#include "Wall.h"
#include "Point.h"
#include "ViewPort.h"
#include "CollisionService.h"
#include "Vector.h"
#include "Polygon.h"
#include "Time.h"

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
        auto initialHitbox = car.Hitbox();
        car.Update(time);
        auto finalPosition = car.Position();
        auto collided = false;
        Vector travel{finalPosition - initialPosition};
        Distance travelRatio { 1.0 };
        
        for(const auto& wall:  pImpl->Walls)
        {
            auto collidedRatio = CollisionService::CheckCollision(initialHitbox, wall.Hitbox(), travel);
            if(collidedRatio < travelRatio)
            {
                travelRatio = collidedRatio;
                finalPosition = initialPosition + travel * travelRatio;
                collided = true;
            }
        }

        if(finalPosition != car.Position())
        {
            car.Collide(initialPosition, finalPosition, time);
        }
        else if(collided)
        {
            car.Update(-std::max(time.Value(), 30));
        }
        
        
        pImpl->View.Update(car.Position());
   }
}
