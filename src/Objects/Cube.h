#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    static bool checkInCube(Ray r, double t);

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
};


#endif //RAYTRACER_CUBE_H
