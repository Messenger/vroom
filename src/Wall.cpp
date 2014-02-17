#include "Wall.h"
#include <cmath>
#include "Point.h"
#include "Distance.h"
#include "Angle.h"

struct Wall::Impl
{
    Point Start;
    Point End;
    
    Impl(const Point& start, const Point& end)
        : Start(start)
        , End(end)
    {
    }
};

Wall::Wall(const Point& start, const Point& end)
    : pImpl(new Impl(start, end))
{
}

Wall::~Wall() 
{    
}

Wall::Wall(Wall&& wall)
    : pImpl(std::move(wall.pImpl))
{
}

Point Wall::Start() const
{
    return pImpl->Start;
}

Angle Wall::Direction() const
{
    auto distance = pImpl->End - pImpl->Start;
    return Angle::Radians(std::atan2(distance.Y().Value(), distance.X().Value()));
}

Distance Wall::Distance() const
{
    return std::sqrt(std::pow((pImpl->End.X() - pImpl->Start.X()).Value(), 2) 
                   + std::pow((pImpl->End.Y() - pImpl->Start.Y()).Value(), 2));
}

static double CalculateDeterminant(const Point& first, const Point& second)
{
    return ((first.X() * second.Y()) - (first.Y() * second.X())).Value();
}

bool Wall::Intersects(const Point& start, const Point& end, Point& collision) const
{
    auto startDifference = start - pImpl->Start;
    auto lineDistance = end - start;
    auto wallDistance = pImpl->End - pImpl->Start;
    
    auto lineIntersectionDeterminate = CalculateDeterminant(wallDistance, startDifference);
    auto wallIntersectionDeterminate = CalculateDeterminant(lineDistance, startDifference);
    auto divisorDeterminate = CalculateDeterminant(lineDistance, wallDistance);
    auto lineIntersectionProportion = lineIntersectionDeterminate / divisorDeterminate;
    auto wallIntersectionProportion = wallIntersectionDeterminate / divisorDeterminate;

    // Collision detected within the line segments
    if(lineIntersectionProportion >= 0 && lineIntersectionProportion <= 1 
    && wallIntersectionProportion >= 0 && wallIntersectionProportion <= 1)
    {
        collision = start + lineIntersectionProportion * lineDistance;
        return true;
    }

    // No collision
    return false; 
}