#ifndef RAYTRACER_LIGHTSOURCE_H
#define RAYTRACER_LIGHTSOURCE_H

#include "../Math/Vec4.h"
#include "../Math/Matrix4.h"

// Assume perfect point source
class LightSource {
private:
    Vec4 position;
    Vec4 direction;
    Vec4 inversePos{};
public:
    LightSource(const Vec4 &position, const Vec4 &direction);

    LightSource transform(Matrix4 trans);

    virtual double calculateIntensity(Vec4 normal, Vec4 hitPoint);

    const Vec4 &getPosition() const;
    const Vec4 &getDirection() const;
};


#endif //RAYTRACER_LIGHTSOURCE_H
