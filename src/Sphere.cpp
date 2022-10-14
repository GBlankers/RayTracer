#include "Sphere.h"

Collision Sphere::checkCollision(Ray r) {
    // Inverse transform the ray
    trans inverseT = this->getT().getInverseTransformation();
    Vec4 newRayStart = r.getStartPoint() + inverseT.translation;
    Vec4 newRayDirection = r.getDirectionVector().pointMultiplication(inverseT.scale);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(newRayDirection, newRayDirection);
    double B = 2.0 * Vec4::dot(newRayStart, newRayDirection);
    double C = Vec4::dot(newRayStart, newRayStart) - 1;

    // Discriminant
    double D = pow(B, 2)-4*A*C;

    // Default value for t, if t<0 then there is no intersection
    double t = -1.0;

    // Check for positive discriminant -> there is an intersection
    if (D>0){
        double t1 = (-B - sqrt(D))/(2.0*A);
        double t2 = (-B + sqrt(D))/(2.0*A);
        t = (t1>t2) ? t2 : t1;
        // Check for color
    }

    return {r.getStartPoint()+(r.getDirectionVector()*t), t, 0, 0, 0};
}

Sphere::Sphere(const Transformation &t) : Shape(t) {}
