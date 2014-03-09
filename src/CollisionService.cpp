#include "CollisionService.h"
#include "Rectangle.h"
#include "Vector.h"
#include "Interval.h"

bool CollisionService::Check(const Rectangle& first, const Rectangle& second) const
{
    auto edges = first.Edges();
    edges.splice(edges.end(), second.Edges());
    for(const auto& edge : edges)
    {
        auto axis = edge.Normal().Normalize();
        auto firstProjection = first.Project(axis);
        auto secondProjection = second.Project(axis);
        
        if(!firstProjection.Overlaps(secondProjection)) {
            return false;
        }
    }

    return true;
}
