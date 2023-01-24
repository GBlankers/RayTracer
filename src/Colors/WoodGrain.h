#ifndef RAYTRACER_WOODGRAIN_H
#define RAYTRACER_WOODGRAIN_H

#include "Color.h"

class WoodGrain : public Color{
private:
    double M, K, N, B;
public:
    explicit WoodGrain(double M = 12, double K = 4, double N = 0.4, double B = 0.006);
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_WOODGRAIN_H
