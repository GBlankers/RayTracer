#include "Vec4.h"

// Constructor
Vec4::Vec4(double x, double y, double z, int homogeneous) : x(x), y(y), z(z), homogeneous(homogeneous){}

void Vec4::reset() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->homogeneous = 0;
}

// Operator overloading to implement vector math
Vec4 Vec4::operator+(const Vec4 vector) const {
    return {this->x+vector.getX(), this->y+vector.getY(), this->z+vector.getZ(), this->homogeneous+vector.getHomogeneous()};
}

Vec4 Vec4::operator-(Vec4 vector) const {
    return {this->x-vector.getX(), this->y-vector.getY(), this->z-vector.getZ(), this->homogeneous-vector.getHomogeneous()};
}


Vec4 Vec4::operator*(double t) const {
    return {this->x*t, this->y*t, this->z*t, 0};
}

Vec4 Vec4::operator*(Vec4 vector) const {
    return {this->getX()*vector.getX(), this->getY()*vector.getY(), this->getZ()*vector.getZ(), 0};
}

Vec4 Vec4::operator/(double t) const {
    return {x/t, y/t, z/t, 0};
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

Vec4 &Vec4::operator+=(const Vec4 &rhs){
    this->x += rhs.getX();
    this->y += rhs.getY();
    this->z += rhs.getZ();
    return *this;
}

double Vec4::dot(Vec4 vector1, Vec4 vector2) {
    return vector1.getX()*vector2.getX()+vector1.getY()*vector2.getY()+vector1.getZ()*vector2.getZ();
}

Vec4 Vec4::cross(Vec4 vector1, Vec4 vector2) {
    return {(vector1.getY()*vector2.getZ()-vector1.getZ()*vector2.getY()), -(vector1.getX()*vector2.getZ()-vector1.getZ()*vector2.getX()),
            (vector1.getX()*vector2.getY()-vector1.getY()*vector2.getX()), 0};
}

Vec4 Vec4::normalize(Vec4 vector) {
    double length = sqrt(pow(vector.getX(), 2) + pow(vector.getY(), 2) + pow(vector.getZ(), 2));
    return {vector.getX()/length, vector.getY()/length, vector.getZ()/length, 0};
}

double Vec4::length(Vec4 vector) {
    return sqrt(pow(vector.getX(), 2)+ pow(vector.getY(), 2)+ pow(vector.getZ(), 2));
}

Vec4 Vec4::clamp(Vec4 vector) {
    return {std::clamp<double>(vector.getX(), 0, 1),
            std::clamp<double>(vector.getY(), 0, 1),
            std::clamp<double>(vector.getZ(), 0, 1), 1};
}

Vec4 Vec4::random(double min, double max) {
    return {randomDouble(min, max), randomDouble(min, max), randomDouble(min, max), 0};
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

void Vec4::setHomogeneous(int argHomogeneous) {
    Vec4::homogeneous = argHomogeneous;
}

Vec4::Vec4(double theta, double phi) {
    this->homogeneous = 0;
    assert(theta>=-90 and theta <= 90);
    assert(phi>=0 and phi <= 360);
    this->x = 1*sin(theta)*sin(phi);
    this->y = 1*cos(theta);
    this->z = 1*sin(theta)*cos(phi);
}
