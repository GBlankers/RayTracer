#ifndef RAYTRACER_VEC4_H
#define RAYTRACER_VEC4_H

#include <cmath>

class Vec4 {
private:
    double x, y, z;
    int homogeneous; // 1 if it is a point, 0 if it is a vector
public:
    // Constructor
    Vec4(double x, double y, double z, int homogeneous);
    explicit Vec4() = default;

    void normalize();
    // Operator overloading
    Vec4 operator+(Vec4 vector) const;
    Vec4 operator-(Vec4 vector) const;
    Vec4 operator*(double t) const;
    bool operator==(const Vec4 &rhs) const;
    bool operator!=(const Vec4 &rhs) const;
    // Dot + cross product between 2 vec4's
    static double dot(Vec4 vector1, Vec4 vector2);
    static Vec4 cross(Vec4 vector1, Vec4 vector2);
    // Basic get/set
    double getX() const;
    double getY() const;
    double getZ() const;
    int getHomogeneous() const;
    void setHomogeneous(int homogeneous);
};


#endif //RAYTRACER_VEC4_H
