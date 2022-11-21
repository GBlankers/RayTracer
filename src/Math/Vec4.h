#ifndef RAYTRACER_VEC4_H
#define RAYTRACER_VEC4_H

#include <cmath>
#include <cassert>
#include <algorithm>
#include "Utils.h"

class Vec4 {
private:
    double x, y, z;
    int homogeneous; // 1 if it is a point, 0 if it is a vector
public:
    // Constructor
    Vec4(double x, double y, double z, int homogeneous);
    // Constructor for a unit length vector using spherical coordinates
    Vec4(double theta, double phi);
    explicit Vec4() = default;

    void reset();
    // Operator overloading
    Vec4 operator+(Vec4 vector) const;
    Vec4 operator-(Vec4 vector) const;
    Vec4 operator*(double t) const;
    Vec4 operator*(Vec4 vector) const;
    Vec4 operator/(double t) const;
    bool operator==(const Vec4 &rhs) const;
    bool operator!=(const Vec4 &rhs) const;
    Vec4& operator+=(const Vec4 &rhs);
    // math between 2 vec4's
    static double dot(Vec4 vector1, Vec4 vector2);
    static Vec4 cross(Vec4 vector1, Vec4 vector2);
    static double length(Vec4 vector);
    static Vec4 normalize(Vec4 vector);
    static Vec4 clamp(Vec4 vector);
    static Vec4 random(double min, double max);
    // Basic get/set
    double getX() const;
    double getY() const;
    double getZ() const;
    int getHomogeneous() const;
    void setHomogeneous(int homogeneous);
};


#endif //RAYTRACER_VEC4_H
