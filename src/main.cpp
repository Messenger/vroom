#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Vroooooooooooooom!",
                                   0, 0, 640, 480,
                                   SDL_WINDOW_RESIZABLE |
                                   SDL_WINDOW_OPENGL);
    IMG_Init( IMG_INIT_PNG );
    auto spriteSheet = IMG_Load( "content/CarSprite.png" );
    SDL_Rect carPosition = { 320, 240 };
    SDL_Rect spritePosition = { 0, 0, 40, 40};
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

        carPosition.y--;
        auto screenSurface = SDL_GetWindowSurface( window );
        SDL_FillRect( screenSurface, NULL, 0 );
        SDL_BlitSurface(spriteSheet, &spritePosition, screenSurface, &carPosition);
        SDL_UpdateWindowSurface( window );
        SDL_Delay( 1000 / 60 );
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}

