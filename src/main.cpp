#include "sdl/Game.h"
#include "World.h"
#include "Car.h"
#include "Wall.h"
#include "Point.h"

int main(int argc, char **argv)
{
    Game game;
    World world;
    Car player1;
    player1.Position(Point(20, 20));
    world.Cars().push_back(std::move(player1));
    world.Walls().push_back(std::move(Wall(Point(160,120), Point(480,120))));
    world.Walls().push_back(std::move(Wall(Point(480,120), Point(480,360))));
    world.Walls().push_back(std::move(Wall(Point(160,120), Point(160,360))));
    world.Walls().push_back(std::move(Wall(Point(160,360), Point(480,360))));
    world.Walls().push_back(std::move(Wall(Point(0,0), Point(0,480))));
    world.Walls().push_back(std::move(Wall(Point(0,480), Point(640,480))));
    world.Walls().push_back(std::move(Wall(Point(640,480), Point(640,0))));
    world.Walls().push_back(std::move(Wall(Point(640,0), Point(0,0))));
    
    while (game.Running()) {
        game.UpdateFrame(world);
    }

    return 0;
}

