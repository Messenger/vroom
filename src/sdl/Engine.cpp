#include "Engine.h"

#include <SDL2/SDL.h>
#include <vector>

#include "Input.h"
#include "Time.h"
#include "Systems/System.h"

struct Engine::Impl
{
    std::vector<std::unique_ptr<System>> Systems;
    Input Input;
};

Engine::Engine()
    : pImpl(new Impl())
{
}

Engine::~Engine()
{

}

Input& Engine::GetInput()
{
    return pImpl->Input;
}

void Engine::Add(std::unique_ptr<System> system)
{
    pImpl->Systems.push_back(std::move(system));
}

void Engine::Run()
{
    for(auto& system : pImpl->Systems)
    {
        system->Start();
    }

    Time lastFrame = 0;
    auto running = true;
    while(running)
    {
        auto initialTime = SDL_GetTicks();
        pImpl->Input.Clear();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                pImpl->Input.PressKey(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                pImpl->Input.ReleaseKey(event.key.keysym.sym);
                break;
            }
        }

        Time updateTime = (SDL_GetTicks()) - lastFrame;
        lastFrame = SDL_GetTicks();
        for(auto& system : pImpl->Systems)
        {
            system->Update(updateTime);
        }

        auto delay = std::max(1000.0 / 60.0 - (SDL_GetTicks() - initialTime), 0.0);
        SDL_Delay( delay );
    }

    for(auto& system : pImpl->Systems)
    {
        system->Stop();
    }
}
