#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

#include "Math/Vec4.h"
#include "Objects/objectProperties.h"
#include "Ray.h"

class Collision {
private:
    Ray incoming; // incoming ray
    double t = -1; // time of the collision to determine the place at the ray
    Vec4 hitPoint{};
    Vec4 normal{}; // normal at the collision point
    bool inside = false;
    LightComponents lightComponents;
    Material material;
public:
    Collision(Ray incoming, double t, Vec4 normal, bool inside, LightComponents lightComponents, Material material);
    Collision();

    // getters
    double getT() const;
    const Vec4 &getColor() const;
    const Vec4 &getCollisionPoint() const;
    const Vec4 &getNormal() const;
    double getReflectivity() const;
    double getTransparency() const;
    bool isInside() const;
    double getRefractiveIndex() const;
    const LightComponents &getLightComponents() const;
    const Material &getMaterial() const;

    const Ray &getIncoming() const;

    // setter
    void setReflectivity(double reflectivity);
};

#endif //RAYTRACER_COLLISION_H


