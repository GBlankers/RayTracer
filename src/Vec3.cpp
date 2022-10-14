#include "Vec3.h"

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

double Vec3::getX() const {
    return x;
}

void Vec3::setX(double newX) {
    Vec3::x = newX;
}

double Vec3::getY() const {
    return y;
}

void Vec3::setY(double newY) {
    Vec3::y = newY;
}

double Vec3::getZ() const {
    return z;
}

void Vec3::setZ(double newZ) {
    Vec3::z = newZ;
}

Vec3 Vec3::operator+(const Vec3 vector) const {
    return {this->x+vector.getX(), this->y+vector.getY(), this->z+vector.getZ()};
}

Vec3 Vec3::operator*(double t) const {
    return {this->x*t, this->y*t, this->z*t};
}

double Vec3::dot(Vec3 vector1, Vec3 vector2) {
    return vector1.getX()*vector2.getX()+vector1.getY()*vector2.getY()+vector1.getZ()*vector2.getZ();
}

Vec3::Vec3() = default;
