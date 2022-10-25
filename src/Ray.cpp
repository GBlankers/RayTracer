#include "Ray.h"

Ray::Ray(Vec4 start, Vec4 direction) : startPoint(start), directionVector(direction) {}

Ray::Ray(Vec4 start, Vec4 screenVector, Vec4 upVector) : startPoint(start), screenVector(screenVector), upVector(upVector) {
    this->crossVector = Vec4::cross(screenVector, upVector);
}

Ray::Ray(const Vec4 &startPoint, const Vec4 &directionVector, const Vec4 &screenVector, const Vec4 &upVector)
        : startPoint(startPoint), directionVector(directionVector), screenVector(screenVector), upVector(upVector) {
    this->crossVector = Vec4::cross(screenVector, upVector);
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

Ray Ray::transform(Matrix4 trans) {
    return {trans*this->startPoint, trans*this->directionVector, this->screenVector, this->upVector};
}

void Ray::setPixel(int distance, double width, double height) {
    this->setDirectionVector((startPoint + screenVector*distance + crossVector*width + upVector*height) - this->startPoint);
}

Vec4 Ray::at(double t) const {
    return this->getStartPoint()+(this->getDirectionVector()*t);
}
