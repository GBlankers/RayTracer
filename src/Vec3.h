#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H


class Vec3 {
private:
    double x{}, y{}, z{};
public:
    Vec3(double x, double y, double z);

    Vec3();

    Vec3 operator+(Vec3 vector) const;

    Vec3 operator*(double t) const;

    static double dot(Vec3 vector1, Vec3 vector2);

    // Basic get/set
    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);
};


#endif //RAYTRACER_VEC3_H
