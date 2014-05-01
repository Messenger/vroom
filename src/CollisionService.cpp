#include <cmath>
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
        
    Distance travelRatio = 0.0;
    for(const auto& edge : edges)
    {
        auto axis = edge.Normal().Normalize();
        auto firstProjection = first.Project(axis);
        auto secondProjection = second.Project(axis);

        auto overlapping = firstProjection.Overlaps(secondProjection);
        auto travelingProjection = firstProjection + axis.DotProduct({travel.X_Component(), travel.Y_Component()});
        auto willOverlap = travelingProjection.Overlaps(secondProjection);
        if(!overlapping && !willOverlap) {
            return false;
        }

        if(overlapping) {
            auto overlap = firstProjection.DistanceTo(secondProjection);
            auto travelDistance = axis.DotProduct({travel.X_Component(), travel.Y_Component()});
            auto ratioToHit = overlap/travelDistance;
            if(std::abs(ratioToHit.Value()) < std::abs(travelRatio.Value())) {
                travelRatio = ratioToHit;
            }
        } else {
            auto distance = firstProjection.DistanceTo(secondProjection);
            auto travelDistance = axis.DotProduct({travel.X_Component(), travel.Y_Component()});
            auto ratioToHit = distance/travelDistance;
            if(travelRatio < ratioToHit) {
                travelRatio = ratioToHit;
            }
        } 
    }
    
    collision = first.Center();
    collision += travel * travelRatio;
    
    return true;
}
