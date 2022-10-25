#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include <cassert>
#include "../Math/Vec4.h"
#include "../Collision.h"
#include "../Ray.h"
#include "../Transformation.h"
#include "LightSource.h"

class Shape {
private:
    Transformation t;
    Vec4 color;
public:
    explicit Shape(Transformation t, Vec4 color);

    virtual Collision checkCollision(Ray r, LightSource l) = 0;
    virtual Vec4 calculateNormal(Vec4 hitPoint) = 0;

    Vec4 getColor(Vec4 hit, double intensity);

    const Transformation &getT() const;
    double getR() const;
    double getG() const;
    double getB() const;
};


#endif //RAYTRACER_SHAPE_H
