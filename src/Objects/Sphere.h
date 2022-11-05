#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include "../Math/Vec4.h"
#include <cmath>

class Sphere: public Shape{
public:
    explicit Sphere(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular, double specularComponent);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;
    Vec4 calculateNormal(Vec4 hitPoint) override;
};


#endif //RAYTRACER_SPHERE_H
