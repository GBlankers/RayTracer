#ifndef RAYTRACER_NORMALROUGHNESS_H
#define RAYTRACER_NORMALROUGHNESS_H

#include "normalManipulator.h"

class normalRoughness : public normalManipulator{
private:
    std::hash<double> doubleHash;
public:
    normalRoughness() = default;
    Vec4 manipulateNormal(Vec4 normal, double roughness, double u, double v, Vec4 worldHit) override;
};


#endif //RAYTRACER_NORMALROUGHNESS_H
