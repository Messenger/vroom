#ifndef COLLISION_SERVICE_H_
#define COLLISION_SERVICE_H_

class Polygon;
class Vector;
class Point;
class Distance;

class CollisionService
{
public:
    static Distance CheckOverlap(const Polygon& first, const Polygon& second);
    static Distance CheckCollision(const Polygon& first, const Polygon& second, const Vector& travel);
};

#endif