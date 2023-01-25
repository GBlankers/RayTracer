#ifndef RAYTRACER_BOOLEANOBJECT_H
#define RAYTRACER_BOOLEANOBJECT_H

#include "../Shape.h"

class BooleanObject : public Shape{
protected:
    std::shared_ptr<Shape> s1, s2;
public:
    BooleanObject(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2);
};


#endif //RAYTRACER_BOOLEANOBJECT_H
