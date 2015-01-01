#include "Accelerate.h"

#include "Time.h"
#include "Entity.h"
#include "Components/Acceleration.h"
#include "Components/Velocity.h"

void Accelerate::Update(const Time& time)
{
    for(auto& entity : Entities())
    {
        auto acceleration = entity.Get<Acceleration>()->Value;
        auto velocityComponent = entity.Get<Velocity>();
        auto& velocity = velocityComponent->Value;
        
        if(acceleration < 0)
        {
            if(velocity > 0) 
            {
                velocity += acceleration * time;
                velocity = std::max(velocity, LinearVelocity(0));
            }
            else 
            {
                velocity -= acceleration * time;
                velocity = std::min(velocity, LinearVelocity(0));
            }
        }
        else
        {
            velocity += acceleration * time;
            velocity = std::min(velocity, velocityComponent->Max);
        }
    }
}
