#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#include "../Math/Vec4.h"

#include <string>
#include <vector>

class Color {
public:
    explicit Color() = default;

    /**
     * Get the color of an object at a specific hit point. Give multiple coordinate possibilities for more variability
     * @param u uv-mapped -> between 0 and 1
     * @param v uv-mapped -> between 0 and 1
     * @param localHit hit in local coordinates
     * @param worldHit hit in world coordinates
     * @return the color at the hit point
     */
    virtual Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) = 0;
};


#endif //RAYTRACER_COLOR_H
