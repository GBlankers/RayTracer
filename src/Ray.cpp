#include "Ray.h"

Ray::Ray(Vec3 start, Vec3 direction) : startPoint(start), directionVector(direction) {}

const Vec3 &Ray::getStartPoint() const {
    return startPoint;
}

const Vec3 &Ray::getDirectionVector() const {
    return directionVector;
}
