#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include "Collision.h"
#include "Ray.h"
#include "Transformation.h"

class Shape {
private:
    Transformation t;
public:
    explicit Shape(Transformation t);
    virtual Collision checkCollision(Ray r) = 0;
    const Transformation &getT() const;
};


#endif //RAYTRACER_SHAPE_H
