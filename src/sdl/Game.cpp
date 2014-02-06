#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <list>
#include "World.h"
#include "Time.h"
#include "Car.h"
#include "Point.h"
#include "Distance.h"
#include "Input.h"

struct Game::Impl
{
    SDL_Window* Window;
    SDL_Surface* SpriteSheet;
    Input Input;
    Time LastFrame;
    bool Running;
    
    Impl()
    : LastFrame(0)
    , Running(true)
    {
    }
};

Game::Game()
    : pImpl(new Impl())
{
    SDL_Init(SDL_INIT_VIDEO);
    pImpl->Window = SDL_CreateWindow("Vroooooooooooooom!",
                                   0, 0, 640, 480,
                                   SDL_WINDOW_RESIZABLE |
                                   SDL_WINDOW_OPENGL);
    IMG_Init( IMG_INIT_PNG );
    pImpl->SpriteSheet = IMG_Load( "content/CarSprite.png" );
}

Game::~Game()
{
    SDL_DestroyWindow( pImpl->Window );
    SDL_Quit();
}

bool Game::Running() const
{
    return pImpl->Running;
}

void Game::UpdateFrame(World& world)
{
    auto initialTime = SDL_GetTicks();
    pImpl->Input.Clear();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            pImpl->Running = false;
            break;
        case SDL_KEYDOWN:
            pImpl->Input.PressKey(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            pImpl->Input.ReleaseKey(event.key.keysym.sym);
            break;
        }
    }

    if(pImpl->Input.IsHeld(SDLK_UP))
    {
        world.Cars().front().StartAccelerating();
    } 
    else  
    {
        world.Cars().front().StopAccelerating();
    }
    
    if(pImpl->Input.IsHeld(SDLK_LEFT))
    {
        world.Cars().front().StartTurningLeft();
    } 
    else if(pImpl->Input.IsHeld(SDLK_RIGHT))
    {
        world.Cars().front().StartTurningRight();
    } 
    else 
    {
        world.Cars().front().StopTurning();
    }
    
    world.Update(Time(SDL_GetTicks()) - pImpl->LastFrame);
    pImpl->LastFrame = SDL_GetTicks();

    auto screenSurface = SDL_GetWindowSurface( pImpl->Window );
    SDL_FillRect( screenSurface, NULL, 0 );
    std::for_each(world.Cars().begin(), world.Cars().end(),
        [&] (const Car& car) { 
        SDL_Rect carPosition = { car.Position().X().Value(), car.Position().Y().Value() };
        SDL_Rect spritePosition = { 0, 0, 40, 40};
        SDL_BlitSurface(pImpl->SpriteSheet, &spritePosition, screenSurface, &carPosition);
    });

    SDL_UpdateWindowSurface( pImpl->Window );
    SDL_Delay( 1000 / 60 - (SDL_GetTicks() - initialTime) );
}
