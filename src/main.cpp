#include "sdl/Game.h"
#include "World.h"

int main(int argc, char **argv)
{
    Game game;
    World world;
    while (game.Running()) {
        game.UpdateFrame(world);
    }

    return 0;
}

