#include "Input.h"
#include <map>

struct Input::Impl
{
    std::map<SDL_Keycode, bool> Pressed;
    std::map<SDL_Keycode, bool> Released;
    std::map<SDL_Keycode, bool> Held;
};

Input::Input()
    : pImpl(new Impl)
{
}

Input::~Input()
{
}

void Input::Clear()
{
    pImpl->Pressed.clear();
    pImpl->Released.clear();
}


void Input::PressKey(SDL_Keycode key)
{
    pImpl->Pressed[key] = true;
    pImpl->Held[key] = true;
}

void Input::ReleaseKey(SDL_Keycode key)
{
    pImpl->Released[key] = true;
    pImpl->Held[key] = false;
}
    
bool Input::IsPressed(SDL_Keycode key) const
{
    return pImpl->Pressed[key];
}

bool Input::IsReleased(SDL_Keycode key) const
{
    return pImpl->Released[key];
}

bool Input::IsHeld(SDL_Keycode key) const
{
    return pImpl->Held[key];
}
