#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, double r, double g, double b);
    Collision checkCollision(Ray r) override;
};


#endif //RAYTRACER_CUBE_H
