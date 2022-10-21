#include "Ray.h"

Ray::Ray(Vec4 start, Vec4 direction) : startPoint(start), directionVector(direction) {}

Ray::Ray(Vec4 start, Vec4 screenVector, Vec4 upVector) : startPoint(start), screenVector(screenVector), upVector(upVector) {
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

void Ray::transform(Matrix4 trans) {
    this->startPoint = trans * this->startPoint;
    this->directionVector = trans * this->directionVector;
}

void Ray::setPixel(int distance, int width, int height) {
    this->setDirectionVector((startPoint + screenVector*distance + crossVector*width + upVector*height) - this->startPoint);
}
