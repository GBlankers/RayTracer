#include "Sphere.h"

Collision Sphere::checkCollision(Ray r) {
    // Inverse transform the ray

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = pow(r.getVx(), 2) + pow(r.getVy(), 2) + pow(r.getVz(), 2);
    double B = 2.0 * (r.getX() * r.getVx() + r.getY() * r.getVy() + r.getZ() * r.getVz());
    double C = pow(r.getX(), 2) + pow(r.getY(), 2) + pow(r.getZ(), 2) - 1;

    // Discriminant
    double D = pow(B, 2)-4*A*C;

    // Default value for t, if t<0 then there is no intersection
    double t = -1.0;

    // Check for positive discriminant -> there is an intersection
    if (D>0){
        double t1 = (-B - sqrt(D))/(2.0*A);
        double t2 = (-B + sqrt(D))/(2.0*A);
        t = (t1>t2) ? t2 : t1;
    }

    // Check for color

    return {r.getX()+ r.getVx() * t, r.getY() + r.getVy() * t, r.getZ() + r.getVz() * t, t, 0, 0, 0};
}

Sphere::Sphere(const Transformation &t) : Shape(t) {}
