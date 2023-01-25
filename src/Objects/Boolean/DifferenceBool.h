#ifndef RAYTRACER_DIFFERENCEBOOL_H
#define RAYTRACER_DIFFERENCEBOOL_H

#include "BooleanObject.h"

/**
 * Implementation for difference boolean objects where the second object s2 will be subtracted for the first one s1
 */
class DifferenceBool : public BooleanObject{
public:
    DifferenceBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;

    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
};


#endif //RAYTRACER_DIFFERENCEBOOL_H
