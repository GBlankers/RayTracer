#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../Math/Vec4.h"

#include <string>
#include <vector>

class Color {
public:
    explicit Color() = default;
    virtual Vec4 getColor(const std::string &objectName, Vec4 direction) = 0;
};


#endif //RAYTRACER_COLOR_H
