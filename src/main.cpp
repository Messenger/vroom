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
    player1.Position({80, 80});
    world.Cars().push_back(std::move(player1));
    world.Walls().push_back(std::move(Wall({200,200}, {800,200})));
    world.Walls().push_back(std::move(Wall({200,200}, {200,600})));
    world.Walls().push_back(std::move(Wall({200,600}, {800,600})));
    world.Walls().push_back(std::move(Wall({400,400}, {1000,400})));
    world.Walls().push_back(std::move(Wall({0,0},     {0,800})));
    world.Walls().push_back(std::move(Wall({0,800},   {1000,800})));
    world.Walls().push_back(std::move(Wall({1000,800},{1000,0})));
    world.Walls().push_back(std::move(Wall({1000,0},  {0,0})));
    
    while (game.Running()) {
        game.UpdateFrame(world);
    }

    return 0;
}

