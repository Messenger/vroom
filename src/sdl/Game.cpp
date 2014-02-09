#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <algorithm>
#include <list>
#include <cmath>
#include "World.h"
#include "Time.h"
#include "Car.h"
#include "Point.h"
#include "Angle.h"
#include "Distance.h"
#include "Input.h"

struct Game::Impl
{
    SDL_Window* Window;
    SDL_Surface* SpriteSheet;
    SDL_GLContext Context;
    Input Input;
    Time LastFrame;
    bool Running;
    
    Impl()
    : LastFrame(0)
    , Running(true)
    {
    }
    
    void SDLDraw(World& world)
    {
        auto screenSurface = SDL_GetWindowSurface( Window );
        SDL_FillRect( screenSurface, NULL, 0 );
        std::for_each(world.Cars().begin(), world.Cars().end(),
            [&] (const Car& car) { 
            SDL_Rect carPosition = { car.Position().X().Value(), car.Position().Y().Value() };
            SDL_Rect spritePosition = { 0, 0, 40, 40};
            SDL_BlitSurface(SpriteSheet, &spritePosition, screenSurface, &carPosition);
        });
        SDL_UpdateWindowSurface( Window );
    }

    void OpenGLDraw(World& world)
    {
        SDL_GL_SetSwapInterval(1);
        glClearColor ( 0.0, 0.0, 0.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );
        std::for_each(world.Cars().begin(), world.Cars().end(),
            [&] (const Car& car) { 
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, SpriteSheet->format->BytesPerPixel, 
                        SpriteSheet->w, SpriteSheet->h, 0, 
                        GL_RGBA, GL_UNSIGNED_BYTE, SpriteSheet->pixels);

            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
            glEnable( GL_TEXTURE_2D );
            glBegin(GL_QUADS);
                glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
                glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
                glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
                glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
            glEnd();
            glLoadIdentity();
            glTranslatef((car.Position().X().Value() - 320.)/320., (car.Position().Y().Value() - 240.)/240., 0);
            glRotatef(car.Direction().Value() + 90, 0, 0, 1);
            glTranslatef(-40/640., -40/480., 0);
        });

        glFlush();
        SDL_GL_SwapWindow(Window);
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
    pImpl->Context = SDL_GL_CreateContext(pImpl->Window);
}

Game::~Game()
{
    SDL_GL_DeleteContext(pImpl->Context);
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

    pImpl->OpenGLDraw(world);
    auto delay = std::max(1000.0 / 60.0 - (SDL_GetTicks() - initialTime), 0.0);
    SDL_Delay( delay );
}
