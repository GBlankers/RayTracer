#ifndef RAYTRACER_CONE_H
#define RAYTRACER_CONE_H

#include "Shape.h"

class Cone : public Shape{
public:
    bool checkHit(Ray r) override;

    Cone(const Transformation &t, const Vec4 &color);

    Collision checkCollision(Ray r, std::vector<std::shared_ptr<LightSource>> l, std::vector<std::shared_ptr<Shape>> worldObjects) override;

    Vec4 calculateNormal(Vec4 hitPoint) override;
};


#endif //RAYTRACER_CONE_H
