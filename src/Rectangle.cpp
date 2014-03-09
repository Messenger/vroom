#include "Rectangle.h"
#include "Point.h"
#include "Vector.h"
#include "Interval.h"

struct Rectangle::Impl
{
    Point Origin;
    Distance Width;
    Distance Height;
    
    Impl(const Point& origin, const Distance& width, const Distance& height)
        : Origin(origin)
        , Width(width)
        , Height(height)
    {
    }
};

Rectangle::Rectangle(const Point& origin, const Distance& width, const Distance& height)
    : pImpl(new Impl{origin, width, height})
{

}

Rectangle::~Rectangle() = default;

Point Rectangle::LowerLeft() const
{
    return pImpl->Origin;
}

Point Rectangle::LowerRight() const
{
    return pImpl->Origin + Point{ pImpl->Width, 0 };
}

Point Rectangle::UpperLeft() const
{
    return pImpl->Origin + Point{ 0, pImpl->Height };
}

Point Rectangle::UpperRight() const
{
    return pImpl->Origin + Point{ pImpl->Width, pImpl->Height};
}


std::list<Vector> Rectangle::Edges() const
{
    return std::list<Vector> {
        { LowerRight() - LowerLeft()},
        { UpperLeft() - LowerLeft() },
        { UpperRight() - LowerRight() },
        { UpperRight() - UpperLeft() }
    };
}

std::list<Point> Rectangle::Points() const
{
    return std::list<Point> {
        LowerLeft(),
        LowerRight(),
        UpperLeft(),
        UpperRight()
    };
}

Interval Rectangle::Project(Vector axis) const
{
    auto min = axis.DotProduct(LowerLeft());
    auto max = axis.DotProduct(LowerLeft());
    for(const auto& point : Points())
    {
        auto dp = axis.DotProduct(point);
        min = std::min(min, dp);
        max = std::max(max, dp);
    }
    
    return {min, max};
}
