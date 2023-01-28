#ifndef RAYTRACER_CONE_H
#define RAYTRACER_CONE_H

#include "Shape.h"

class Cone : public Shape{
public:
    explicit Cone(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
    SingleColor* getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    static bool insideUnitCone(Vec4 hitPoint);

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_CONE_H
