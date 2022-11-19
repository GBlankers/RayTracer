#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

#include "Math/Vec4.h"

class Collision {
private:
    Vec4 collisionPoint{}; // location of the collision
    double t = -1; // time of the collision to determine the place at the ray
    Vec4 color{}; // color of the shape where this collision has happened
    Vec4 normal{};
    double reflectivity, transparency;
public:
    Collision(Vec4 collisionPoint, double t, Vec4 color, Vec4 normal, double reflectivity);

    explicit Collision() = default;

    double getT() const;
    const Vec4 &getColor() const;
    const Vec4 &getCollisionPoint() const;
    const Vec4 &getNormal() const;
    double getReflectivity() const;
};

#endif //RAYTRACER_COLLISION_H


