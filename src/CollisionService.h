#ifndef COLLISION_SERVICE_H_
#define COLLISION_SERVICE_H_

class Polygon;
class Vector;
class Point;

class CollisionService
{
public:
    static bool CheckOverlap(const Polygon& first, const Polygon& second);
    static bool CheckCollision(const Polygon& first, const Polygon& second, const Vector& travel);
    static bool CheckCollision(const Polygon& first, const Polygon& second, const Vector& travel, Point& collision);
};

#endif