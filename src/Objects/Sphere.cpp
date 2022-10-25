#include "Sphere.h"

Sphere::Sphere(const Transformation &t, Vec4 color) : Shape(t, color) {}

Collision Sphere::checkCollision(Ray r, LightSource l) {
    // Inverse transform the ray
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    l.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = 2.0 * Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;

    // Discriminant
    double D = pow(B, 2)-4*A*C;

    // Default value for t, if t<0 then there is no intersection
    double t;

    // Check for positive discriminant -> there is an intersection
    if (D>0){
        double t1 = (-B - sqrt(D))/(2.0*A);
        double t2 = (-B + sqrt(D))/(2.0*A);
        t = (t1>t2) ? t2 : t1;

        // Calculate hit point in local coordinates
        Vec4 hit = transformedRay.at(t);
        // Calculate the normal vector at that point
        Vec4 normal = calculateNormal(hit);
        // Get the intensity of the light source
        double intensity = l.calculateIntensity(normal, hit);

        return {r.at(t), t, this->getColor(hit, intensity)};
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint) {
    Vec4 normal = hitPoint;
    normal.setHomogeneous(0);
    normal.normalize();
    return normal;
}