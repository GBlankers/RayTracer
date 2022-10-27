#include "Plane.h"

Plane::Plane(const Transformation &t, Vec4 color) : Shape(t, color){}

// Default plane at y=0
Collision Plane::checkCollision(Ray r, LightSource l) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    l.transform(inverse);

    // Ray is not parallel to the plane
    if(transformedRay.getDirectionVector().getY() != 0.0){
        double t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();

        if(t>0 and t < 700){
            Vec4 hit = transformedRay.at(t);
            Vec4 normal = calculateNormal(hit);

            return {r.at(t), t, this->getIntensityCorrectedColor(hit, l.calculateIntensity(normal, hit))};
        }
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

Vec4 Plane::calculateNormal(Vec4 hitPoint) {
    return Vec4({0, 1, 0, 0});
}

Vec4 Plane::getIntensityCorrectedColor(Vec4 hit, double intensity) {
    if(checkerBoard){
        bool black;
        if(hit.getZ()<0){
            black = (((int)hit.getX()/800) + ((int)hit.getZ()/800)) % 2 == 0;
        } else {
            black = (((int)hit.getX()/800) + ((int)hit.getZ()/800)) % 2 == 1;
        }
        if (black){
            this->setColor({0, 0, 0, 0});
        } else {
            this->setColor({1, 1, 1, 0});
        }
    }
    return Shape::getIntensityCorrectedColor(hit, intensity);
}

void Plane::setCheckerBoardPattern(bool b) {
    this->checkerBoard = b;
}
