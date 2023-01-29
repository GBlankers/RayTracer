#ifndef RAYTRACER_BOOLEANOBJECT_H
#define RAYTRACER_BOOLEANOBJECT_H

#include "../Shape.h"
#include <utility>

/**
 * Parent boolean class. Used for default implementations and common variables.
 */
class BooleanObject : public Shape{
protected:
    // Boolean operators will be calculated with these 2 objects.
    std::shared_ptr<Shape> s1, s2;
public:
    BooleanObject(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t);

    // Default implementations -> will not be used in the specific boolean objects
    // so provide a default implementation in this parent class
    bool checkHit(Ray r, double &t, bool &inside, double &t2) override;
    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;
    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
    SingleColor *getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) override;
};


#endif //RAYTRACER_BOOLEANOBJECT_H
