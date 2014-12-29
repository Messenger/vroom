#ifndef SDL_RENDER_H_
#define SDL_RENDER_H_

#include "Systems/System.h"
#include <memory>

class Time;

class Render : public System
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Render();
    ~Render();

    void Start();
    void Update(const Time& time);
    void Stop();
};

#endif