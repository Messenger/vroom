#include "World.h"
#include <list>
#include <algorithm>
#include "Car.h"

struct World::Impl
{
    std::list<Car> Cars;
    
    Impl()
        : Cars()
    {
        Cars.push_back(std::move(Car()));
    }
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

void World::Update(const Time& time)
{
    std::for_each(pImpl->Cars.begin(), pImpl->Cars.end(),
        [&] (Car& car) { car.Update(time); });
}
