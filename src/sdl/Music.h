#ifndef SDL_MUSIC_H_
#define SDL_MUSIC_H_

#include "Systems/System.h"

class Time;

class Music : public System
{
public:
    void Start();
    void Update(const Time& time);
};

#endif