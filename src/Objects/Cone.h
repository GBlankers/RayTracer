#ifndef RAYTRACER_CONE_H
#define RAYTRACER_CONE_H

#include "Shape.h"

class Cone : public Shape{
public:
    explicit Cone(const Transformation &t, LightComponents lightComponents, Material material);
    explicit Cone(const Transformation &t, const std::string& path, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;
};


#endif //RAYTRACER_CONE_H
