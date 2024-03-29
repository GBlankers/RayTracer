#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

#include "Math/Vec4.h"
#include "Objects/objectProperties.h"
#include "Ray.h"

/**
 * Collision class to keep all the important information about a collision
 */
class Collision {
private:
    Ray incoming; // incoming ray
    double t = -1; // time of the collision to determine the place at the ray
    double t2 = -1;
    Vec4 hitPoint{};
    Vec4 normal{}; // normal at the collision point
    bool inside = false;
    LightComponents lightComponents;
    Vec4 color; // cannot be in lightComponents because seg fault
    Material material;
public:
    Collision(Ray incoming, double t, Vec4 normal, bool inside, LightComponents lightComponents, Material material, double t2 = -1);
    Collision();

    // getters
    double getT() const;
    double getT2() const;
    const Vec4 &getColor() const;
    const Vec4 &getCollisionPoint() const;
    const Vec4 &getNormal() const;
    bool isInside() const;
    double getRefractiveIndex() const;
    const LightComponents &getLightComponents() const;
    const Material &getMaterial() const;
    const Ray &getIncoming() const;

    // setter
    void setReflectivity(double reflectivity);
};

#endif //RAYTRACER_COLLISION_H


