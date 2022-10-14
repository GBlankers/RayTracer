#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vec3.h"

class Ray {
private:
    Vec3 startPoint; // Starting point
    Vec3 directionVector; // Direction
public:
    Ray(Vec3 start, Vec3 direction);

    const Vec3 &getStartPoint() const;

    const Vec3 &getDirectionVector() const;
};

#endif //RAYTRACER_RAY_H
