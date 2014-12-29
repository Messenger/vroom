#include "Movement.h"

#include <vector>

#include "Time.h"
#include "Entity.h"
#include "Components/Velocity.h"
#include "Components/Position.h"
#include "Components/Direction.h"
#include "Vector.h"

void Movement::Update(const Time& time)
{
    for(auto& entity : Entities())
    {
        auto& velocity = entity.Get<Velocity>()->Value;
        auto& position = entity.Get<Position>()->Value;
        auto& direction = entity.Get<Direction>()->Value;
        position += Vector(time * velocity, direction);
    }
}
