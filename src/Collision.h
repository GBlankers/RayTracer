#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

#include "Math/Vec4.h"

class Collision {
private:
    Vec4 collisionPoint; // location of the collision
    double t; // time of the collision to determine the place at the ray
    double r, g, b; // color of the shape where this collision has happened

public:
    Collision(Vec4 collisionPoint, double t, double r, double g, double b);

    double getT() const;
};

#endif //RAYTRACER_COLLISION_H


