#ifndef RAYTRACER_CHECKERBOARD_H
#define RAYTRACER_CHECKERBOARD_H

#include "Color.h"
#include "../settings.h"

class CheckerBoard : public Color{
private:
    Vec4 color1, color2;
    double checkerBoardSize;
public:
    CheckerBoard(Vec4 c1, Vec4 c2, double size);
    Vec4 getColor(const std::string &objectType, double u, double v, Vec4 localHit, Vec4 worldHit) override;
    Vec4 getColor() override;
};


#endif //RAYTRACER_CHECKERBOARD_H
