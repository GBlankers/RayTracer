#ifndef RAYTRACER_DIFFERENCEBOOL_H
#define RAYTRACER_DIFFERENCEBOOL_H

#include "BooleanObject.h"
#include <utility>

/**
 * Implementation for difference boolean objects where the second object s2 will be subtracted for the first one s1
 */
class DifferenceBool : public BooleanObject{
public:
    DifferenceBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t) override;

    const LightComponents &getLightComponents() const override;
    SingleColor *getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;

    bool isPointInside(Vec4 hitPoint) const override;
};


#endif //RAYTRACER_DIFFERENCEBOOL_H
