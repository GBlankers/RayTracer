#include "Plane.h"

Plane::Plane(const Transformation &t, double r, double g, double b) : Shape(t, r, g, b){}

// Default plane at y=0
Collision Plane::checkCollision(Ray r, LightSource l) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    LightSource transformedLight = l.transform(inverse);

    double t = -1, t1, t2;

    // Ray is not parallel to the plane
    if(transformedRay.getDirectionVector().getY() != 0.0){
        t1 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        t2 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        t = (t1>t2) ? t2 : t1;

        Vec4 hit = transformedRay.getStartPoint()+(transformedRay.getDirectionVector()*t);
        Vec4 normal = calculateNormal(hit);

        Vec4 normalizedDirection = transformedLight.getPosition()-hit;
        normalizedDirection.normalize();

        double intensity, angle;
        angle = acos(Vec4::dot(normal, normalizedDirection));

        if(angle > M_PI_2){
            intensity = 0.0;
        } else {
            intensity = 1-(angle/M_PI_2);
        }
        return {r.getStartPoint()+(r.getDirectionVector()*t), t, this->getR()*intensity, this->getG()*intensity,
                this->getB()*intensity};
    }

    return {{0,0,0,0}, -1, 0, 0, 0};
}

Vec4 Plane::calculateNormal(Vec4 hitPoint) {
    return Vec4({0, 1, 0, 0});
}
