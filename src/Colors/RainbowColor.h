#ifndef RAYTRACER_RAINBOWCOLOR_H
#define RAYTRACER_RAINBOWCOLOR_H

#include "Color.h"

class RainbowColor : public Color{
public:
    RainbowColor() = default;
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_RAINBOWCOLOR_H
