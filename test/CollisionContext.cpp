#include <igloo/igloo.h>
#include "CollisionService.h"
#include "Polygon.h"
#include "Point.h"
#include "Vector.h"

using namespace igloo;

Context(collision)
{
    Spec(should_determine_two_rectangles_are_overlapping)
    {
        auto first = Polygon::Rectangle({0,0},10,10);
        auto second = Polygon::Rectangle({5,5},10,10);
        
        auto result = CollisionService::CheckOverlap(first, second);
        Assert::That(result, Is().True());
    }

    Spec(should_determine_two_rectangles_are_not_overlapping)
    {
        auto first = Polygon::Rectangle({0,0},10,10);
        auto second = Polygon::Rectangle({50,50},10,10);
        
        auto result = CollisionService::CheckOverlap(first, second);
        Assert::That(result, Is().False());
    }
    
    Spec(should_determine_two_rectangles_aligned_on_the_x_axis_are_not_overlapping)
    {
        auto first = Polygon::Rectangle({50,0},10,10);
        auto second = Polygon::Rectangle({50,50},10,10);
        
        auto result = CollisionService::CheckOverlap(first, second);
        Assert::That(result, Is().False());
    }
    
    Spec(should_determine_two_rectangles_aligned_on_the_y_axis_are_not_overlapping)
    {
        auto first = Polygon::Rectangle({0,50},10,10);
        auto second = Polygon::Rectangle({50,50},10,10);
        
        auto result = CollisionService::CheckOverlap(first, second);
        Assert::That(result, Is().False());
    }
    
    Spec(should_determine_rectangle_collides_with_other_rectangle)
    {
        auto first = Polygon::Rectangle({0,50},10,10);
        auto second = Polygon::Rectangle({50,50},10,10);
        Vector lineOfTravel{100, Angle::East()};
        
        auto result = CollisionService::CheckCollision(first, second, lineOfTravel);
        Assert::That(result, Is().True());
    }

    Spec(should_determine_rectangle_does_not_collide_with_rectangle_that_is_too_far_away)
    {
        auto first = Polygon::Rectangle({0,50},10,10);
        auto second = Polygon::Rectangle({50,50},10,10);
        Vector lineOfTravel{10, Angle::East()};
        
        auto result = CollisionService::CheckCollision(first, second, lineOfTravel);
        Assert::That(result, Is().False());
    }
    
    Spec(should_determine_rectangle_collides_with_rectangle_diagonally)
    {
        auto first = Polygon::Rectangle({0,0},10,10);
        auto second = Polygon::Rectangle({50,50},10,10);
        Vector lineOfTravel{100, 45};
        
        auto result = CollisionService::CheckCollision(first, second, lineOfTravel);
        Assert::That(result, Is().True());
    }

    Spec(should_determine_rectangle_collision_center)
    {
        auto first = Polygon::Rectangle({0,0},10,10);
        auto second = Polygon::Rectangle({50,0},10,10);
        Vector lineOfTravel{41, Angle::East()};
        
        Point collision{0,0};
        CollisionService::CheckCollision(first, second, lineOfTravel, collision);
        Assert::That(collision, Is().EqualTo(Point{45,5}));
    }
};