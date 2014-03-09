#include <igloo/igloo.h>
#include "CollisionService.h"
#include "Rectangle.h"
#include "Point.h"

using namespace igloo;

Context(collision)
{
    Spec(should_determine_two_rectangles_are_overlapping)
    {
        Rectangle first{{0,0},10,10};
        Rectangle second{{5,5},10,10};
        
        auto result = service.Check(first, second);
        Assert::That(result, Is().True());
    }

    Spec(should_determine_two_rectangles_are_not_overlapping)
    {
        Rectangle first{{0,0},10,10};
        Rectangle second{{50,50},10,10};
        
        auto result = service.Check(first, second);
        Assert::That(result, Is().False());
    }
    
    Spec(should_determine_two_rectangles_aligned_on_the_x_axis_are_not_overlapping)
    {
        Rectangle first{{50,0},10,10};
        Rectangle second{{50,50},10,10};
        
        auto result = service.Check(first, second);
        Assert::That(result, Is().False());
    }
    
    Spec(should_determine_two_rectangles_aligned_on_the_y_axis_are_not_overlapping)
    {
        Rectangle first{{0,50},10,10};
        Rectangle second{{50,50},10,10};
        
        auto result = service.Check(first, second);
        Assert::That(result, Is().False());
    }

    CollisionService service;
};