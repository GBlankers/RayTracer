#ifndef RAYTRACER_INTERSECTIONBOOL_H
#define RAYTRACER_INTERSECTIONBOOL_H

#include "BooleanObject.h"

/**
 * Implementation for the intersection boolean object
 */
class IntersectionBool : public BooleanObject{
public:
    IntersectionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t) override;

    SingleColor *getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_INTERSECTIONBOOL_H
