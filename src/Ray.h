#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Math/Vec4.h"
#include "Math/Matrix4.h"

/**
 * Ray class with the parameters of the ray as well as methods to transform the ray and to get the hit point at a certain time point
 */
class Ray {
private:
    Vec4 startPoint; // Starting point
    Vec4 directionVector; // Direction
public:
    Ray() = default;
    Ray(Vec4 start, Vec4 direction);

    Ray transform(Matrix4 trans);
    Vec4 at(double t) const;

    void setStartPoint(const Vec4 &startPoint);
    void setDirectionVector(const Vec4 &directionVector);
    const Vec4 &getStartPoint() const;
    const Vec4 &getDirectionVector() const;
};

#endif //RAYTRACER_RAY_H
