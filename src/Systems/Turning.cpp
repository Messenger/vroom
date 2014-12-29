#include "Turning.h"

#include "Entity.h"
#include "Components/Rotation.h"
#include "Components/Direction.h"

void Turning::Update(const Time& time)
{
    for(auto& entity : Entities())
    {
        auto& rotation = entity.Get<Rotation>()->Value;
        auto& direction = entity.Get<Direction>()->Value;
        direction += time * rotation;
    }
}
