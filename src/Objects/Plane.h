#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"
#include "LightSource.h"

class Plane : public Shape{
public:
    explicit Plane(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;

    bool isPointInside(Vec4 hitPoint) const override;

    SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;
};


#endif //RAYTRACER_PLANE_H
