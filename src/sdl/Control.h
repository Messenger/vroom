#ifndef SDL_CONTROL_H_
#define SDL_CONTROL_H_

#include "Systems/System.h"

class Input;

class Control : public System
{
    const Input& input;
    
public:
    Control(const Input& input);
    void Update(const Time& time);
};

#endif