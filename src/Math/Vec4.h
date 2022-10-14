#ifndef RAYTRACER_VEC4_H
#define RAYTRACER_VEC4_H


class Vec4 {
private:
    double x, y, z;
    int homogeneous;
public:
    Vec4(double x, double y, double z, int homogeneous);

    Vec4();

    Vec4 operator+(Vec4 vector) const;

    Vec4 operator*(double t) const;

    int getHomogeneous() const;

    Vec4 pointMultiplication(Vec4 vector2) const;

    static double dot(Vec4 vector1, Vec4 vector2);

    // Basic get/set
    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);
};


#endif //RAYTRACER_VEC4_H
