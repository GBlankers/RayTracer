#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"
#include <cmath>

class Cube : public Shape{
private:
    constexpr static const double tolerance = 0.0000001;
public:
    explicit Cube(const Transformation &t, Vec4 color);
    Collision checkCollision(Ray r, std::vector<std::shared_ptr<LightSource>> l, std::vector<std::shared_ptr<Shape>> worldObjects) override;
    static bool checkInCube(Ray r, double t);

    bool checkHit(Ray r) override;

    Vec4 calculateNormal(Vec4 hitPoint) override;
};


#endif //RAYTRACER_CUBE_H
