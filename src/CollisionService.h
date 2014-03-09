#ifndef COLLISION_SERVICE_H_
#define COLLISION_SERVICE_H_

class Rectangle;

class CollisionService
{
public:
    bool Check(const Rectangle& first, const Rectangle& second) const;
};

#endif