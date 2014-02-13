#include "sdl/Game.h"
#include "World.h"
#include "Car.h"
#include "Wall.h"
#include "Point.h"

int main(int argc, char **argv)
{
    Game game;
    World world;
    world.Cars().push_back(std::move(Car()));
    world.Walls().push_back(std::move(Wall(Point(0,0), Point(0,480))));
    world.Walls().push_back(std::move(Wall(Point(0,480), Point(640,480))));
    world.Walls().push_back(std::move(Wall(Point(640,480), Point(640,0))));
    world.Walls().push_back(std::move(Wall(Point(640,0), Point(0,0))));
    
    while (game.Running()) {
        game.UpdateFrame(world);
    }

    return 0;
}

