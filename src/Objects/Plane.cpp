#include "Plane.h"

Plane::Plane(const Transformation &t, Vec4 color) : Shape(t, color){}

// Default plane at y=0
Collision Plane::checkCollision(Ray r, LightSource l) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    l.transform(inverse);

    double t, t1, t2;

    // Ray is not parallel to the plane
    if(transformedRay.getDirectionVector().getY() != 0.0){
        t1 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        t2 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        t = (t1>t2) ? t2 : t1;

        Vec4 hit = transformedRay.at(t);
        Vec4 normal = calculateNormal(hit);

        double intensity = l.calculateIntensity(normal, hit);

        return {r.at(t), t, this->getColor(hit, intensity)};
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

Vec4 Plane::calculateNormal(Vec4 hitPoint) {
    return Vec4({0, 1, 0, 0});
}
