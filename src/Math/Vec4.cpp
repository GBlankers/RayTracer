#include "Vec4.h"

Vec4::Vec4(double x, double y, double z, int homogeneous) : x(x), y(y), z(z), homogeneous(homogeneous){}

double Vec4::getX() const {
    return x;
}

void Vec4::setX(double newX) {
    Vec4::x = newX;
}

double Vec4::getY() const {
    return y;
}

void Vec4::setY(double newY) {
    Vec4::y = newY;
}

double Vec4::getZ() const {
    return z;
}

void Vec4::setZ(double newZ) {
    Vec4::z = newZ;
}

Vec4 Vec4::operator+(const Vec4 vector) const {
    return {this->x+vector.getX(), this->y+vector.getY(), this->z+vector.getZ(), this->homogeneous+vector.getHomogeneous()};
}

Vec4 Vec4::operator*(double t) const {
    return {this->x*t, this->y*t, this->z*t, 0};
}

double Vec4::dot(Vec4 vector1, Vec4 vector2) {
    return vector1.getX()*vector2.getX()+vector1.getY()*vector2.getY()+vector1.getZ()*vector2.getZ();
}

Vec4 Vec4::pointMultiplication(Vec4 vector2) const {
    return {this->getX()*vector2.getX(), this->getY()*vector2.getY(), this->getZ()*vector2.getZ(), 0};
}

int Vec4::getHomogeneous() const {
    return homogeneous;
}

Vec4::Vec4() = default;
