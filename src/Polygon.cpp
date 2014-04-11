#include "Polygon.h"
#include "Vector.h"
#include "Point.h"
#include "Interval.h"

struct Polygon::Impl 
{
    std::list<Point> Points;
};

Polygon::Polygon(std::list<Point> points)
    : pImpl(new Impl{points})
{

}

Polygon::~Polygon() = default;

Polygon::Polygon(Polygon&& polygon)
    : pImpl(std::move(polygon.pImpl))
{
}

Polygon Polygon::Rectangle(const Point& origin, const Distance& width, const Distance& height)
{
    return Polygon({
        origin,
        origin + Point{ width, 0},
        origin + Point{ width, height},
        origin + Point{ 0, height}
    });
}

Point Polygon::Center() const
{
    auto origin = pImpl->Points.front();
    auto minX = origin.X();
    auto minY = origin.Y();
    auto maxX = origin.X();
    auto maxY = origin.Y();

    for(const auto& point : pImpl->Points)
    {
        minX = std::min(point.X(), minX);
        minY = std::min(point.Y(), minY);
        maxX = std::max(point.X(), maxX);
        maxY = std::max(point.Y(), maxY);
    }
    
    return { (maxX - minX) / 2. + minX, 
             (maxY - minY) / 2. + minY };
}

std::list<Vector> Polygon::Edges() const
{
    std::list<Vector> edges;
    const Point* lastPoint = nullptr;
    for(const auto& point : pImpl->Points)
    {
        if(lastPoint != nullptr)
        {
            edges.push_back({point - *lastPoint});
        }
        lastPoint = &point;
    }
    edges.push_back({pImpl->Points.front() - *lastPoint});

    return edges;
}

std::list<Point> Polygon::Points() const
{
    return pImpl->Points;
}

Interval Polygon::Project(Vector axis) const
{
    auto firstPoint = axis.DotProduct(pImpl->Points.front());
    auto min = firstPoint;
    auto max = firstPoint;
    for(const auto& point : pImpl->Points)
    {
        auto dp = axis.DotProduct(point);
        min = std::min(min, dp);
        max = std::max(max, dp);
    }
    
    return {min, max};
}
