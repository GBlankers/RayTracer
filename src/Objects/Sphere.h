#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include "../Math/Vec4.h"
#include <cmath>

class Sphere: public Shape{
public:
    explicit Sphere(const Transformation &t, Vec4 color);

    Collision checkCollision(Ray r, LightSource l) override;
    Vec4 calculateNormal(Vec4 hitPoint) override;
};


#endif //RAYTRACER_SPHERE_H
