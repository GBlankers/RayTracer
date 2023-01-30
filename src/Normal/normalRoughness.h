#ifndef RAYTRACER_NORMALROUGHNESS_H
#define RAYTRACER_NORMALROUGHNESS_H

#include "normalManipulator.h"

/**
 * Use the roughness parameter to randomly change the normals
 */
class normalRoughness : public normalManipulator{
private:
    /**
     * Use hashes of the coordinates to generate the random values
     */
    std::hash<double> doubleHash;
public:
    normalRoughness() = default;
    Vec4 manipulateNormal(Vec4 normal, double roughness, double u, double v, Vec4 worldHit) override;
};


#endif //RAYTRACER_NORMALROUGHNESS_H
