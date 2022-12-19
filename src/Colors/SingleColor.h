#ifndef RAYTRACER_SINGLECOLOR_H
#define RAYTRACER_SINGLECOLOR_H


#include "Color.h"

class SingleColor : public Color{
private:
    Vec4 c;
public:
    explicit SingleColor(Vec4 c);
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_SINGLECOLOR_H
