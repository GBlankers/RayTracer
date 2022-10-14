#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"
#include <cmath>

class Cube: public Shape{
public:
    explicit Cube(const Transformation &t);

    Collision checkCollision(Ray r) override;
};


#endif //RAYTRACER_CUBE_H
