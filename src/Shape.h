#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include <cassert>
#include "Collision.h"
#include "Ray.h"
#include "Transformation.h"

class Shape {
private:
    Transformation t;
    double r, g, b;
public:
    explicit Shape(Transformation t, double R, double G, double B);

    virtual Collision checkCollision(Ray r) = 0;

    const Transformation &getT() const;
    double getR() const;
    double getG() const;
    double getB() const;
};


#endif //RAYTRACER_SHAPE_H
