#ifndef RAYTRACER_MARBLE_H
#define RAYTRACER_MARBLE_H

#include "Color.h"

class Marble: public Color{
public:
    Marble() = default;
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_MARBLE_H
