#include "Plane.h"

Plane::Plane(const Transformation &t, Vec4 color) : Shape(t, color){}

// Default plane at y=0
Collision Plane::checkCollision(Ray r, std::vector<std::shared_ptr<LightSource>> l, std::vector<std::shared_ptr<Shape>> worldObjects) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Ray is not parallel to the plane
    if(transformedRay.getDirectionVector().getY() != 0.0){
        double t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();

        if(t>0){
            // Calculate the hit point in local coordinates
            Vec4 hitPoint = transformedRay.at(t);
            // Calculate the light intensity
            double intensity = 0;
            std::vector<bool> hitVector;
            for(const auto& light: l){
                light->transform(inverse);
                for(const auto& s: worldObjects){
                    if(s.get() != this)
                        hitVector.push_back(s->checkHit(Ray{r.at(t),(light->getPosition()-r.at(t))}));
                }
                if(!std::count(hitVector.begin(), hitVector.end(), true))
                    intensity += light->calculateIntensity(calculateNormal(hitPoint), hitPoint);
            }
            return {r.at(t), t, getIntensityCorrectedColor(hitPoint, intensity/(double)l.size())};
        }
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

bool Plane::checkHit(Ray r) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    double t=-1;

    // Ray is not parallel to the plane
    if(transformedRay.getDirectionVector().getY() != 0.0)
        t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();

    return t>0;
}

Vec4 Plane::calculateNormal(Vec4 hitPoint) {
    return Vec4({0, 1, 0, 0});
}

Vec4 Plane::getIntensityCorrectedColor(Vec4 hit, double intensity) {
    if(checkerBoard){
        bool check;
        if(hit.getZ()<0){
            check = (((int)hit.getX()/800) + ((int)hit.getZ()/800)) % 2 == 0;
        } else {
            check = (((int)hit.getX()/800) + ((int)hit.getZ()/800)) % 2 == 1;
        }
        if (check){
            return {0, 0, 0, 0};
        }
    }
    return Shape::getIntensityCorrectedColor(hit, intensity);
}

void Plane::setCheckerBoardPattern(bool b) {
    this->checkerBoard = b;
}
