#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include "Vec3.h"
#include <cmath>

class Sphere: public Shape{
public:
    explicit Sphere(const Transformation &t);

    Collision checkCollision(Ray r) override;
};


#endif //RAYTRACER_SPHERE_H
