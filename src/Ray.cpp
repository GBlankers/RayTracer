#include "Ray.h"

Ray::Ray(Vec4 start, Vec4 direction) : startPoint(start), directionVector(direction) {}

Ray Ray::transform(Matrix4 trans) {
    return {trans * this->startPoint, trans * this->directionVector};
}

Vec4 Ray::at(double t) const {
    return this->getStartPoint()+(this->getDirectionVector()*t);
}

const Vec4 &Ray::getStartPoint() const {
    return startPoint;
}

const Vec4 &Ray::getDirectionVector() const {
    return directionVector;
}

void Ray::setStartPoint(const Vec4 &startPointArg) {
    Ray::startPoint = startPointArg;
}

void Ray::setDirectionVector(const Vec4 &directionVectorArg) {
    Ray::directionVector = directionVectorArg;
}
