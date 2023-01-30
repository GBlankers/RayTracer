#ifndef RAYTRACER_UNIONBOOL_H
#define RAYTRACER_UNIONBOOL_H

#include "BooleanObject.h"
#include <utility>

/**
 * Implementation for the union boolean object
 */
class UnionBool : public BooleanObject{
public:
    UnionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t) override;

    const LightComponents &getLightComponents() const override;
    SingleColor *getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_UNIONBOOL_H
