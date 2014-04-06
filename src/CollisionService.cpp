#include <limits>
#include "CollisionService.h"
#include "Polygon.h"
#include "Vector.h"
#include "Interval.h"
#include "Point.h"

bool CollisionService::CheckOverlap(const Polygon& first, const Polygon& second)
{
    return CheckCollision(first, second, {0,0});
}

bool CollisionService::CheckCollision(const Polygon& first, const Polygon& second, const Vector& travel)
{
    Point zero{0,0};
    return CheckCollision(first, second, travel, zero);
}

bool CollisionService::CheckCollision(const Polygon& first, const Polygon& second, const Vector& travel, Point& collision)
{
    auto edges = first.Edges();
    edges.splice(edges.end(), second.Edges());
    
    Vector translationAxis{0,0};
    Distance minOverlap{std::numeric_limits<double>::infinity()};
    
    for(const auto& edge : edges)
    {
        auto axis = edge.Normal().Normalize();
        auto firstProjection = first.Project(axis);
        auto secondProjection = second.Project(axis);

        auto overlapping = firstProjection.Overlaps(secondProjection);
        firstProjection += axis.DotProduct({travel.X_Component(), travel.Y_Component()});
        auto willOverlap = firstProjection.Overlaps(secondProjection);
        if(!overlapping && !willOverlap) {
            return false;
        }
        
        auto amountOfOverlap = -firstProjection.DistanceTo(secondProjection);
        if(amountOfOverlap < minOverlap)
        {
            minOverlap = amountOfOverlap;
            translationAxis = axis;
            Vector distance{first.Center() - second.Center()};
            auto value = distance.DotProduct({translationAxis.X_Component(), translationAxis.Y_Component()});
            if(value > 0)
            {
                translationAxis = -translationAxis;
            }
        }
    }
    
    collision = first.Center();
    collision += travel;
    collision += translationAxis * minOverlap ;
    
    return true;
}
