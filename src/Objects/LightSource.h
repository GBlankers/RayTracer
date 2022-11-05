#ifndef RAYTRACER_LIGHTSOURCE_H
#define RAYTRACER_LIGHTSOURCE_H

#include "../Math/Vec4.h"
#include "../Math/Matrix4.h"

// Assume perfect point source
class LightSource {
private:
    Vec4 position;
    Vec4 direction{};
    Vec4 inversePos{};
    Vec4 color{};
    double intensity;
public:
    LightSource(const Vec4 &position, const Vec4 &pointsAt, double intensity);

    LightSource transform(Matrix4 trans);

    virtual double calculateDiffuse(Vec4 normal, Vec4 hitPoint);
    virtual double calculateSpecular(Vec4 normal, Vec4 viewDirection, Vec4 hitPoint);

    const Vec4 &getPosition() const;
    const Vec4 &getDirection() const;
    const Vec4 &getColor() const;
    const Vec4 &getInversePos() const;

    double getIntensity() const;
};


#endif //RAYTRACER_LIGHTSOURCE_H
