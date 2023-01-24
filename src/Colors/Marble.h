#ifndef RAYTRACER_MARBLE_H
#define RAYTRACER_MARBLE_H

#include "Color.h"
#include "../Math/Noise.h"

class Marble: public Color{
private:
    Noise n{};
public:
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
    static double undulate(double x);
};


#endif //RAYTRACER_MARBLE_H
