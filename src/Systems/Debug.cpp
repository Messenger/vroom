#include "Debug.h"

#include <iostream>
#include "Entity.h"
#include "Components/Rotation.h"
#include "Components/Direction.h"
#include <Components/Acceleration.h>
#include <Components/Velocity.h>

void Debug::Update(const Time& time)
{
    for(auto& entity : Entities())
    {
        auto& rotation = entity.Get<Rotation>()->Value;
        auto& direction = entity.Get<Direction>()->Value;
        auto& acceleration = entity.Get<Acceleration>()->Value;
        auto& velocity = entity.Get<Velocity>()->Value;
        std::cout << "Rotation: " << rotation.Value() << std::endl;
        std::cout << "Direction: " << direction.Value() << std::endl;
        std::cout << "Acceleration: " << acceleration.Value() << std::endl;
        std::cout << "Velocity: " << velocity.Value() << std::endl;
    }
}
