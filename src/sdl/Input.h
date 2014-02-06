#ifndef SDL_INPUT_H_
#define SDL_INPUT_H_

#include <SDL2/SDL.h>
#include <memory>

class Input
{
    struct Impl;
    std::unique_ptr<Impl> pImpl;
    
public:
    Input();
    ~Input();
    
    void Clear();
    
    void PressKey(SDL_Keycode key);
    void ReleaseKey(SDL_Keycode key);
    
    bool IsPressed(SDL_Keycode key) const;
    bool IsReleased(SDL_Keycode key) const;
    bool IsHeld(SDL_Keycode key) const;
};

#endif