#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

#include "Math/Vec4.h"

class Collision {
private:
    Vec4 collisionPoint{}; // location of the collision
    double t = -1; // time of the collision to determine the place at the ray
    Vec4 color{}; // color of the shape where this collision has happened
    Vec4 normal{};
    double reflectivity=0, transparency=0, refractiveIndex=1; // Material properties at the collision point
    bool inside;
public:
    Collision(Vec4 collisionPoint, double t, Vec4 color, Vec4 normal, bool inside, double reflectivity, double transparency, double refractiveIndex);

    explicit Collision() = default;

    double getT() const;
    const Vec4 &getColor() const;
    const Vec4 &getCollisionPoint() const;
    const Vec4 &getNormal() const;
    double getReflectivity() const;
    double getTransparency() const;
    bool isInside() const;
    double getRefractiveIndex() const;

    void setReflectivity(double reflectivity);
};

#endif //RAYTRACER_COLLISION_H


