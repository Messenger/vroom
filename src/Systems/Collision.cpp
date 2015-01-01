#include "Collision.h"

#include <cmath>
#include <iostream>

#include "Entity.h"
#include "Vector.h"
#include "Polygon.h"
#include "Time.h"
#include "Components/Velocity.h"
#include "Components/Size.h"
#include "Components/Position.h"
#include "Components/Direction.h"
#include "Components/State.h"
#include "Components/Rotation.h"
#include "CollisionService.h"

void Collision::Update(const Time& time)
{
    for(auto& moving : Entities())
    {
        if(moving.Has<Velocity>())
        {
            auto& mVelocity = moving.Get<Velocity>()->Value;
            auto& mPosition = moving.Get<Position>()->Value;
            auto& mDirection = moving.Get<Direction>()->Value;
            auto mState = moving.Get<State>();
            
            Polygon mHitbox({
                mPosition + Vector{ 20, mDirection} + Vector{ 10, mDirection + 90},
                mPosition + Vector{ 10, mDirection + 90} + Vector{ 20, mDirection + 180},
                mPosition + Vector{ 20, mDirection + 180} + Vector{ 10, mDirection + 270},
                mPosition + Vector{ 10, mDirection + 270} + Vector{ 20, mDirection},
            });
            
            bool collided = false;
            Distance travelRatio { 1.0 };
            Vector travel{ mVelocity * time, mDirection };
            for(auto& stationary : Entities())
            {
                if(!stationary.Has<Velocity>())
                {
                    auto& sPosition = stationary.Get<Position>()->Value;
                    auto& sDirection = stationary.Get<Direction>()->Value;
                    auto sSize = stationary.Get<Size>();
                    
                    auto halfHeight = sSize->Height / 2.;
                    auto halfWidth = sSize->Width / 2.;

                    Polygon sHitbox({
                        sPosition + Vector{ halfWidth, sDirection} + Vector{ halfHeight, sDirection + 90},
                        sPosition + Vector{ halfHeight, sDirection + 90} + Vector{ halfWidth, sDirection + 180},
                        sPosition + Vector{ halfWidth, sDirection + 180} + Vector{ halfHeight, sDirection + 270},
                        sPosition + Vector{ halfHeight, sDirection + 270} + Vector{ halfWidth, sDirection}
                    });

                    auto collidedRatio = CollisionService::CheckCollision(mHitbox, sHitbox, travel);
                    if(collidedRatio < travelRatio)
                    {
                        travelRatio = collidedRatio;
                        collided = true;
                    }
                }
            }
            
            mPosition += travel * travelRatio;
            if(collided)
            {
                if(mState->Collided && mVelocity != 0)
                {
                    mVelocity = -mVelocity;
                    auto collisionDistance = travel.Magnitude().Value() * (1. - travelRatio.Value());
                    auto minimumImpulse = std::max(std::abs(collisionDistance), 1.);
                    mPosition += Vector{ mVelocity > 0 ? minimumImpulse : -minimumImpulse, mDirection};
                }

                auto& rotation = moving.Get<Rotation>()->Value;
                auto& direction = moving.Get<Direction>()->Value;
                direction -= time * rotation;
            }
            
            mState->Collided = collided;
        }
    }
}
