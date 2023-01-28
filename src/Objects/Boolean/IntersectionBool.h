#ifndef RAYTRACER_INTERSECTIONBOOL_H
#define RAYTRACER_INTERSECTIONBOOL_H

#include "BooleanObject.h"

class IntersectionBool : public BooleanObject{
public:
    IntersectionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
    IntersectionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_INTERSECTIONBOOL_H
