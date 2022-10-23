#include "Sphere.h"

Sphere::Sphere(const Transformation &t, double r, double g, double b) : Shape(t, r, g, b) {}

Collision Sphere::checkCollision(Ray r, LightSource l) {
    // Inverse transform the ray
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    LightSource transformedLight = l.transform(inverse);

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
        Vec4 hit = transformedRay.getStartPoint()+(transformedRay.getDirectionVector()*t);
        // Calculate the normal vector at that point
        Vec4 normal = calculateNormal(hit);
        // Get the direction vector and normalize
        Vec4 normalizedDirection = transformedLight.getPosition()-hit;
        normalizedDirection.normalize();
        // Get the angle between the normal and the direction vector
        double intensity, angle;
        angle = acos(Vec4::dot(normal, normalizedDirection));
        if(angle > M_PI_2){
            intensity = 0.0;
        } else {
            intensity = 1-(angle/M_PI_2);
        }

        return {r.getStartPoint()+(r.getDirectionVector()*t), t, this->getR()*intensity,
                this->getG()*intensity, this->getB()*intensity};
    }

    return {{0,0,0,0}, -1, 0, 0, 0};
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint) {
    Vec4 normal = hitPoint;
    normal.setHomogeneous(0);
    normal.normalize();
    return normal;
}
