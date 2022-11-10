#include "Sphere.h"

Sphere::Sphere(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
               double specularComponent, double reflectivity, double roughness) :
        Shape(t, color, ambient, diffuse, specular, specularComponent, reflectivity, roughness) {}

Collision Sphere::checkCollision(Ray r) {
    double t;

    if (checkHit(r, t)){
        return {r.at(t), t, getColor(), Vec4::normalize(calculateNormal(r.at(t))+Vec4::random(-0.5, 0.5)*getRoughness())};
    }

    return {{0, 0, 0, 0}, -1, {0, 0, 0, 0}, {0, 0, 0, 0}};
}

bool Sphere::checkHit(Ray r, double &t) {
    // Inverse transform the ray
    Matrix4 inverse = getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;
    double D = pow(B, 2) - (A * C);

    t = (-B - sqrt(D))/A;

    // Discriminant >= 0 -> hit
    return t>0;
}

bool Sphere::checkHit(Ray r) {
    // Inverse transform the ray
    Matrix4 inverse = getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;
    double D = pow(B, 2) - (A * C);

    // t >= 0 -> hit
    return (-B-sqrt(D))/A > 0 or (-B+sqrt(D))/A > 0;
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint) {
    Vec4 normal(getT().getInverse()*hitPoint);
    normal.setHomogeneous(0);
    return Vec4::normalize(getT().getForward()*normal);
}
