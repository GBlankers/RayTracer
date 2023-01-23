#ifndef RAYTRACER_WOODGRAIN_H
#define RAYTRACER_WOODGRAIN_H

#include "Color.h"

class WoodGrain : public Color{
public:
    WoodGrain() = default;
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_WOODGRAIN_H
