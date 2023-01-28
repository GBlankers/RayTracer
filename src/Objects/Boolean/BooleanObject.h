#ifndef RAYTRACER_BOOLEANOBJECT_H
#define RAYTRACER_BOOLEANOBJECT_H

#include "../Shape.h"

class BooleanObject : public Shape{
protected:
    std::shared_ptr<Shape> s1, s2;
public:
    BooleanObject(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
    BooleanObject(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    // Default implementations
    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;
    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
    SingleColor *getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;
};


#endif //RAYTRACER_BOOLEANOBJECT_H
