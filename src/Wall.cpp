#include "Wall.h"
#include "Point.h"

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

bool Wall::Intersects(const Point& start, const Point& end, Point& collision) const
{
    auto s1_x = end.X().Value() - start.X().Value();
    auto s1_y = end.Y().Value() - start.Y().Value();
    auto s2_x = pImpl->End.X().Value() - pImpl->Start.X().Value();
    auto s2_y = pImpl->End.Y().Value() - pImpl->Start.Y().Value();

    auto s = (-s1_y * (start.X().Value() - pImpl->Start.X().Value()) + s1_x * (start.Y().Value() - pImpl->Start.Y().Value())) / (-s2_x * s1_y + s1_x * s2_y);
    auto t = ( s2_x * (start.Y().Value() - pImpl->Start.Y().Value()) - s2_y * (start.X().Value() - pImpl->Start.X().Value())) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        collision = Point(start.X().Value() + (t * s1_x),
                          start.Y().Value() + (t * s1_y));
        return true;
    }

    return false; // No collision
}
