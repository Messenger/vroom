#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <list>
#include "Input.h"
#include "World.h"
#include "Time.h"
#include "Car.h"
#include "Point.h"
#include "Distance.h"

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Vroooooooooooooom!",
                                   0, 0, 640, 480,
                                   SDL_WINDOW_RESIZABLE |
                                   SDL_WINDOW_OPENGL);
    IMG_Init( IMG_INIT_PNG );
    auto spriteSheet = IMG_Load( "content/CarSprite.png" );
    SDL_Rect spritePosition = { 0, 0, 40, 40};

    World world;
    Input input;
    int lastTime = 0;
    bool running = true;
    while (running) {
        auto initialTime = SDL_GetTicks();
        input.Clear();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                input.PressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                input.ReleaseKey(event.key.keysym.sym);
                break;
            }
        }

        if(input.IsHeld(SDLK_UP))
        {
            world.Cars().front().StartAccelerating();
        } 
        else  
        {
            world.Cars().front().StopAccelerating();
        }
        
        if(input.IsHeld(SDLK_LEFT))
        {
            world.Cars().front().StartTurningLeft();
        } 
        else if(input.IsHeld(SDLK_RIGHT))
        {
            world.Cars().front().StartTurningRight();
        } 
        else 
        {
            world.Cars().front().StopTurning();
        }
        
        world.Update(Time(SDL_GetTicks() - lastTime));
        lastTime = SDL_GetTicks();

        auto screenSurface = SDL_GetWindowSurface( window );
        SDL_FillRect( screenSurface, NULL, 0 );
        std::for_each(world.Cars().begin(), world.Cars().end(),
            [&] (const Car& car) { 
            SDL_Rect carPosition = { car.Position().X().Value(), car.Position().Y().Value() };
            SDL_BlitSurface(spriteSheet, &spritePosition, screenSurface, &carPosition);
        });

        SDL_UpdateWindowSurface( window );
        SDL_Delay( 1000 / 60 - (SDL_GetTicks() - initialTime) );
    }

    SDL_DestroyWindow( window );
    SDL_Quit();

    return 0;
}

