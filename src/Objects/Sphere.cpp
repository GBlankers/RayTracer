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
    if (D>=0){
        // This part of the quadratic equation will always be smaller than the other part
        t = (-B - sqrt(D))/A;
        // Calculate hitPointL point in local coordinates
        Vec4 hitPointL = transformedRay.at(t);
        // Calculate hit point in world coordinates
        Vec4 hitPointW = r.at(t);
        // Keep track of total intensity
        double intensity = 0;
        // Is there a clear path to the light source?
        bool clearPathToLight;

        // Check all the light sources
        for(const auto& light: l){
            // For every light source, assume that there is a clear path at first
            clearPathToLight = true;
            // Check all the objects in the scene
            for(const auto& obj: worldObjects){
                // Do not check the for an intersection with itself
                // + check if the light is blocked by other objects
                if(obj.get() != this and obj->checkHit(Ray{hitPointW, light->getPosition()-hitPointW})){
                    // There is no clear path to the light -> there will be shadows
                    clearPathToLight = false;
                }
            }
            if(clearPathToLight) {
                light->transform(inverse);
                intensity += light->calculateIntensity(calculateNormal(hitPointL), hitPointL);
            }
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

    return D>=0;
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint) {
    Vec4 normal(hitPoint);
    normal.setHomogeneous(0);
    return Vec4::normalize(normal);
}
