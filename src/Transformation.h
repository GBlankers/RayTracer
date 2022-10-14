#ifndef RAYTRACER_TRANSFORMATION_H
#define RAYTRACER_TRANSFORMATION_H

#include "Vec3.h"

struct trans{
    Vec3 translation;
    //Vec3 scale;
    //Vec3 rotation;
};

class Transformation {
private:
    trans forwardTransformation{};
    trans inverseTransformation{};
public:
    explicit Transformation(trans forwardTransformation);

    Transformation();

    void calculateInverseTransformation();

    const trans &getInverseTransformation() const;
    const trans &getForwardTransformation() const;
};


#endif //RAYTRACER_TRANSFORMATION_H
