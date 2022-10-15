#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Math/Vec4.h"
#include "Math/Matrix4.h"

class Ray {
private:
    Vec4 startPoint; // Starting point
    Vec4 directionVector; // Direction
public:
    Ray(Vec4 start, Vec4 direction);

    void transform(Matrix4 trans);

    void setStartPoint(const Vec4 &startPoint);
    void setDirectionVector(const Vec4 &directionVector);
    const Vec4 &getStartPoint() const;
    const Vec4 &getDirectionVector() const;
};

#endif //RAYTRACER_RAY_H
