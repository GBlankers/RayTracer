#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, LightComponents lightComponents, Material material);
    explicit Cube(const Transformation &t, const std::string& path, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;
    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    static bool checkInCube(Ray r, double t);
};


#endif //RAYTRACER_CUBE_H
