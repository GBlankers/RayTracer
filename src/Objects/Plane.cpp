#include "Plane.h"

Plane::Plane(const Transformation &t, Vec4 color) : Shape(t, color, 0.0) {}

// Default plane at y=0
Collision Plane::checkCollision(Ray r) {
    double t;

    if(checkHit(r, t)){
        return {r.at(t), t, this->getColor()};
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

bool Plane::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    // Ray is not parallel to the plane
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();
        return t>0;
    }
    return false;
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
