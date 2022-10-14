#include "Ray.h"

Ray::Ray(Vec4 start, Vec4 direction) : startPoint(start), directionVector(direction) {}

const Vec4 &Ray::getStartPoint() const {
    return startPoint;
}

const Vec4 &Ray::getDirectionVector() const {
    return directionVector;
}

void Ray::setStartPoint(const Vec4 &startPoint) {
    Ray::startPoint = startPoint;
}

void Ray::setDirectionVector(const Vec4 &directionVector) {
    Ray::directionVector = directionVector;
}
