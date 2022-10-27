#ifndef RAYTRACER_CONE_H
#define RAYTRACER_CONE_H

#include "Shape.h"

class Cone : public Shape{
public:
    Cone(const Transformation &t, const Vec4 &color);

    Collision checkCollision(Ray r, LightSource l) override;

    Vec4 calculateNormal(Vec4 hitPoint) override;
};


#endif //RAYTRACER_CONE_H
