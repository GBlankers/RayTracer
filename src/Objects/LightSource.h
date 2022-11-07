#ifndef RAYTRACER_LIGHTSOURCE_H
#define RAYTRACER_LIGHTSOURCE_H

#include "../Math/Vec4.h"
#include "../Math/Matrix4.h"

// Assume perfect point source
class LightSource {
private:
    Vec4 position;
    Vec4 color{};
public:
    LightSource(const Vec4 &position, const Vec4 &pointsAt, Vec4 color);

    double calculateDiffuse(Vec4 normal, Vec4 hitPoint);
    double calculateSpecular(Vec4 normal, Vec4 viewDirection, Vec4 hitPoint);

    const Vec4 &getPosition() const;
    const Vec4 &getColor() const;
};


#endif //RAYTRACER_LIGHTSOURCE_H
