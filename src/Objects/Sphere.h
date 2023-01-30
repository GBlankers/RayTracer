#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include <cmath>
#include <utility>

/**
 * Implementation of the sphere shape
 */
class Sphere: public Shape{
public:
    explicit Sphere(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
    SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_SPHERE_H
