#include "Sphere.h"

Sphere::Sphere(const Transformation &t, Vec4 color) : Shape(t, color) {}

Collision Sphere::checkCollision(Ray r, std::vector<std::shared_ptr<LightSource>> l, std::vector<std::shared_ptr<Shape>> worldObjects) {
    // Inverse transform the ray
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;

    // Discriminant
    double D = pow(B, 2)-(A*C);

    // Default value for t, if t<0 then there is no intersection
    double t;

    // Check for positive discriminant -> there is an intersection
    if (D>0){
        // This part of the quadratic equation will always be smaller than the other part
        t = (-B - sqrt(D))/A;
        // Calculate hitPointL point in local coordinates
        Vec4 hitPointL = transformedRay.at(t);
        Vec4 hitPointW = r.at(t);
        // Calculate the intensity of the light source
        double intensity = 0;
        std::vector<bool> hitVector;
        for(const auto& light: l){
            light->transform(inverse);
            for(const auto& s: worldObjects){
                if(s.get() != this)
                    hitVector.push_back(s->checkHit(Ray{hitPointW, light->getPosition() - hitPointW}));
            }
            if(!std::count(hitVector.begin(), hitVector.end(), true))
                intensity += light->calculateIntensity(calculateNormal(hitPointL), hitPointL);
        }

        return {hitPointW, t, getIntensityCorrectedColor(hitPointL, intensity / (double) l.size())};
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

bool Sphere::checkHit(Ray r) {
    // Inverse transform the ray
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;

    // Discriminant
    double D = pow(B, 2)-(A*C);

    return D>0;
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint) {
    Vec4 normal = hitPoint;
    normal.setHomogeneous(0);
    normal.normalize();
    return normal;
}
