#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"
#include <cmath>

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, double r, double g, double b);
    Collision checkCollision(Ray r) override;
    static bool checkInCube(Ray r, double t);
};


#endif //RAYTRACER_CUBE_H
