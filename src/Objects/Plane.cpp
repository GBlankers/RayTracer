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
            Vec4 hitPointL = transformedRay.at(t);
            // Calculate the point in world coordinates
            Vec4 hitPointW = r.at(t);
            // Light intensity
            double intensity = 0;
            // Vector to keep track if there were any hits in between the light and the hitpoint
            std::vector<bool> hitVector;
            // Go over all the light sources
            for(const auto& light: l){
                // Check all the world objects
                for(const auto& s: worldObjects){
                    // Do not check the lighting with this object itself
                    if(s.get() != this) {
                        hitVector.push_back(s->checkHit(Ray{hitPointW,(light->getPosition()-hitPointW)}));
                    }
                }
                if(!std::count(hitVector.begin(), hitVector.end(), true)) {
                    light->transform(inverse);
                    intensity += light->calculateIntensity(calculateNormal(hitPointL), hitPointL);
                }
            }
            return {hitPointW, t, getIntensityCorrectedColor(hitPointL, intensity/(double)l.size())};
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
            check = (((int)hit.getX()/this->checkerBoardSize) + ((int)hit.getZ()/this->checkerBoardSize)) % 2 == 0;
        } else {
            check = (((int)hit.getX()/this->checkerBoardSize) + ((int)hit.getZ()/this->checkerBoardSize)) % 2 == 1;
        }
        if (check){
            return {0, 0, 0, 0};
        }
    }
    return Shape::getIntensityCorrectedColor(hit, intensity);
}

void Plane::setCheckerBoardPattern(bool b, int size) {
    this->checkerBoard = b;
    this->checkerBoardSize = size;
}
