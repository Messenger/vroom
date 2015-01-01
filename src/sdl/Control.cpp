#include "Control.h"

#include "Entity.h"
#include "sdl/Input.h"
#include "Components/Acceleration.h"
#include "Components/Keys.h"
#include "Components/Stats.h"
#include "Components/Rotation.h"
#include "Components/State.h"

Control::Control(const Input& input)
    : input(input)
{

}

void Control::Update(const Time& time)
{
    for(auto& entity : Entities())
    {
        auto keys = entity.Get<Keys>();
        auto stats = entity.Get<Stats>();
        auto& acceleration = entity.Get<Acceleration>()->Value;
        
        if(input.IsHeld(keys->Accelerate))
        {
            acceleration = stats->AccelerationRate;
        }
        else
        {
            acceleration = stats->DecelerationRate;
        }
        
        auto& rotation = entity.Get<Rotation>()->Value;

        if(entity.Get<State>()->Collided)
        {
            rotation = 0;
        }
        else if(input.IsHeld(keys->TurnLeft))
        {
            rotation = stats->TurningRate;
        }
        else if(input.IsHeld(keys->TurnRight))
        {
            rotation = -stats->TurningRate;
        }
        else
        {
            rotation = 0;
        }
    }
}
