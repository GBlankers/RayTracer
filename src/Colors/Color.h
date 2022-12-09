#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../Math/Vec4.h"

#include <string>
#include <vector>

class Color {
public:
    explicit Color() = default;
    virtual Vec4 getColor(const std::string &objectType, double u, double v) = 0;
    virtual Vec4 getColor() = 0; // Only for collision object
};


#endif //RAYTRACER_COLOR_H
