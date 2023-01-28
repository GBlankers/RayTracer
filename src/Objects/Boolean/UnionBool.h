#ifndef RAYTRACER_UNIONBOOL_H
#define RAYTRACER_UNIONBOOL_H

#include "BooleanObject.h"
#include <utility>

class UnionBool : public BooleanObject{
public:
    UnionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
    UnionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t) override;
};


#endif //RAYTRACER_UNIONBOOL_H
