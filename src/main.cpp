#include "sdl/Game.h"
#include "World.h"
#include "Car.h"

int main(int argc, char **argv)
{
    Game game;
    World world;
    world.Cars().push_back(std::move(Car()));
    while (game.Running()) {
        game.UpdateFrame(world);
    }

    return 0;
}

