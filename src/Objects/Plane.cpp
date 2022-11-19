#include "Plane.h"

Plane::Plane(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
             double specularComponent, double reflectivity, double roughness) :
        Shape(t, color, ambient, diffuse, specular, specularComponent, reflectivity, roughness) {}

// Default plane at y=0
Collision Plane::checkCollision(Ray r) {
    double t;

    if(checkHit(r, t)){
        if(checkerBoard){
            bool check;
            Vec4 localHit = getT().getInverse()*r.at(t);
            if(localHit.getX()<0){
                if(localHit.getZ()<0){
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 0;
                } else {
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 1;
                }
            } else {
                if(localHit.getZ()<0){
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 1;
                } else {
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 0;
                }
            }
            if(check){
                return {r.at(t), t, {0, 0, 0, 0}, Vec4(), getReflectivity()};
            }
        }
        return {r.at(t), t, getColor(), Vec4::normalize(calculateNormal(r.at(t))+Vec4::random(-0.5, 0.5)*getRoughness()), getReflectivity()};
    }

    return {{0, 0, 0, 0}, -1, {0, 0, 0, 0}, {0, 0, 0, 0}, 0};
}

bool Plane::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    // Ray is not parallel to the plane
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();
        return t>0;
    }
    return false;
}

bool Plane::checkHit(Ray r) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    // Ray is not parallel to the plane
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        return -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY()>0;
    }
    return false;
}

Vec4 Plane::calculateNormal(Vec4 hitPoint) {
    return Vec4::normalize(getT().getForward()*Vec4({0, 1, 0, 0}));
}

void Plane::setCheckerBoardPattern(bool b, int size) {
    this->checkerBoard = b;
    this->checkerBoardSize = size;
}
