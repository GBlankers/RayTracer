#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

#include "Math/Vec4.h"

class Collision {
private:
    Vec4 collisionPoint; // location of the collision
    double t = -1; // time of the collision to determine the place at the ray
    double r=0, g=0, b=0; // color of the shape where this collision has happened

public:
    Collision(Vec4 collisionPoint, double t, double r, double g, double b);

    explicit Collision() = default;

    double getT() const;

    const Vec4 &getCollisionPoint() const;
};

#endif //RAYTRACER_COLLISION_H


