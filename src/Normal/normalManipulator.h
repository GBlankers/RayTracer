#ifndef RAYTRACER_NORMALMANIPULATOR_H
#define RAYTRACER_NORMALMANIPULATOR_H

#include "../Math/Vec4.h"

/**
 * Class to manipulate normals
 */
class normalManipulator {
public:
    explicit normalManipulator() = default;
    virtual Vec4 manipulateNormal(Vec4 normal, double roughness, double u, double v, Vec4 worldHit) = 0;
};


#endif //RAYTRACER_NORMALMANIPULATOR_H
