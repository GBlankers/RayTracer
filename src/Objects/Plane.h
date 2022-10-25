#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"
#include "LightSource.h"

class Plane : public Shape{
public:
    explicit Plane(const Transformation &t, Vec4 color);
    Collision checkCollision(Ray r, LightSource l) override;

    Vec4 calculateNormal(Vec4 hitPoint) override;
};


#endif //RAYTRACER_PLANE_H
