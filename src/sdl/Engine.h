#ifndef SDL_ENGINE_H_
#define SDL_ENGINE_H_

#include <memory>

class System;
class Input;

class Engine
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;

public:
    Engine();
    ~Engine();

    Input& GetInput();
    void Add(std::unique_ptr<System> system);
    void Run();
};

#endif