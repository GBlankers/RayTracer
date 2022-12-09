#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include <cmath>

#include "Shape.h"
#include "objectProperties.h"
#include "../Math/Vec4.h"

class Sphere: public Shape{
public:
    explicit Sphere(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
};


#endif //RAYTRACER_SPHERE_H
