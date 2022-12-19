#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../Math/Vec4.h"

#include <string>
#include <vector>

class Color {
public:
    explicit Color() = default;
    virtual Vec4 getColor(const std::string &objectType, double u, double v, Vec4 localHit, Vec4 worldHit) = 0;
    // Only for collision object -> return default color or the single color in the case of the single color class
    virtual Vec4 getColor() = 0;
};


#endif //RAYTRACER_COLOR_H
