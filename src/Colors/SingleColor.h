#ifndef RAYTRACER_SINGLECOLOR_H
#define RAYTRACER_SINGLECOLOR_H


#include "Color.h"

class SingleColor : public Color{
private:
    Vec4 c;
public:
    explicit SingleColor(Vec4 c);
    Vec4 getColor(const std::string &objectType, double u, double v) override;

    Vec4 getColor() override;
};


#endif //RAYTRACER_SINGLECOLOR_H
