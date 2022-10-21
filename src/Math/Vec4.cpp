#include "Vec4.h"

// Constructor
Vec4::Vec4(double x, double y, double z, int homogeneous) : x(x), y(y), z(z), homogeneous(homogeneous){}


// Operator overloading to implement vector math
Vec4 Vec4::operator+(const Vec4 vector) const {
    return {this->x+vector.getX(), this->y+vector.getY(), this->z+vector.getZ(), this->homogeneous+vector.getHomogeneous()};
}

Vec4 Vec4::operator*(double t) const {
    return {this->x*t, this->y*t, this->z*t, 0};
}

bool Vec4::operator==(const Vec4 &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z &&
           homogeneous == rhs.homogeneous;
}

bool Vec4::operator!=(const Vec4 &rhs) const {
    return !(rhs == *this);
}

double Vec4::dot(Vec4 vector1, Vec4 vector2) {
    return vector1.getX()*vector2.getX()+vector1.getY()*vector2.getY()+vector1.getZ()*vector2.getZ();
}


// Get/set
double Vec4::getX() const {
    return x;
}

double Vec4::getY() const {
    return y;
}

double Vec4::getZ() const {
    return z;
}

int Vec4::getHomogeneous() const {
    return homogeneous;
}
