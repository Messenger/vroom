#include "Render.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include "ViewPort.h"
#include "Entity.h"
#include "Components/Position.h"
#include "Components/Direction.h"
#include "Components/Size.h"
#include "Components/Sprite.h"
#include <Components/Velocity.h>

struct Render::Impl
{
    SDL_Window* Window;
    SDL_Surface* SpriteSheet;
    GLuint Sprite;
    SDL_GLContext Context;
    ViewPort View;
};

Render::Render()
    : pImpl(new Impl())
{

}

Render::~Render()
{

}

void Render::Start()
{
    SDL_Init(SDL_INIT_VIDEO);
    pImpl->Window = SDL_CreateWindow("Vroooooooooooooom!",
                                   0, 0, 640, 480,
                                   SDL_WINDOW_RESIZABLE |
                                   SDL_WINDOW_OPENGL);
    IMG_Init( IMG_INIT_PNG );
    pImpl->SpriteSheet = IMG_Load( "content/CarSprite.png" );
    glGenTextures(1, &pImpl->Sprite);

    pImpl->Context = SDL_GL_CreateContext(pImpl->Window);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable( GL_TEXTURE_2D );
    glBindTexture(GL_TEXTURE_2D, pImpl->Sprite);
    glTexImage2D(GL_TEXTURE_2D, 0, pImpl->SpriteSheet->format->BytesPerPixel, 
                pImpl->SpriteSheet->w, pImpl->SpriteSheet->h, 0, 
                GL_RGBA, GL_UNSIGNED_BYTE, pImpl->SpriteSheet->pixels);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );    
}

void Render::Stop()
{
    SDL_GL_DeleteContext(pImpl->Context);
    SDL_DestroyWindow( pImpl->Window );
    SDL_Quit();
}

static void glTexCoord2d(const Point& point)
{
    glTexCoord2d(point.X().Value(), point.Y().Value());
}

static void glVertex2d(const Point& point)
{
    glVertex2d(point.X().Value(), point.Y().Value());
}

void Render::Update(const Time& time)
{
    for(auto& entity : Entities())
    {
        if(entity.Has<Velocity>())
        {
            auto& position = entity.Get<Position>()->Value;
            pImpl->View.Update(position);
        }
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(pImpl->View.Offset().X().Value(), 
            pImpl->View.Offset().X().Value() + pImpl->View.Width().Value(), 
            pImpl->View.Offset().Y().Value(), 
            pImpl->View.Offset().Y().Value() + pImpl->View.Height().Value(), 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);

    SDL_GL_SetSwapInterval(1);
    glClearColor ( 0.1, 0.1, 0.1, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );

    for(auto& entity : Entities())
    {
        auto& position = entity.Get<Position>()->Value;
        auto& direction = entity.Get<Direction>()->Value;
        auto size = entity.Get<Size>();
        auto sprite = entity.Get<Sprite>();
        
        auto& sUpperLeft = sprite->Offset;
        auto sUpperRight = sUpperLeft + Point(sprite->Width, 0);
        auto sBottomLeft = sUpperLeft + Point(0, sprite->Height);
        auto sBottomRight = sUpperLeft + Point(sprite->Width, sprite->Height);

        Point eUpperLeft(0, 0);
        Point eUpperRight(size->Width, 0);
        Point eBottomLeft(0, size->Height);
        Point eBottomRight(size->Width, size->Height);
        
        glLoadIdentity();
        glTranslatef(position.X().Value(), position.Y().Value(), 0);
        glRotatef(direction.Value() + sprite->Direction.Value(), 0, 0, 1);
        glTranslatef(-size->Width.Value() / 2., -size->Height.Value() / 2., 0);
        glBegin(GL_QUADS);
            glTexCoord2d(sUpperLeft); glVertex2d(eUpperLeft);
            glTexCoord2d(sUpperRight); glVertex2d(eUpperRight);
            glTexCoord2d(sBottomRight); glVertex2d(eBottomRight);
            glTexCoord2d(sBottomLeft); glVertex2d(eBottomLeft);
        glEnd();
    }

    glFlush();
    SDL_GL_SwapWindow(pImpl->Window);
}
