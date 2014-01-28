#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    std::cout << "Hello, vroom!" << std::endl;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindow("Vroooooooooooooom!",
                     0, 0, 640, 480,
                     SDL_WINDOW_RESIZABLE |
                     SDL_WINDOW_OPENGL);
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            }
        }
    }
    return 0;
}

