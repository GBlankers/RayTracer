#include "Plane.h"

Plane::Plane(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

Plane::Plane(const Transformation &t, const std::string& path, LightComponents lightComponents, Material material) :
        Shape(t, path, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

// Default plane at y=0
Collision Plane::checkCollision(Ray r) {
    double t;
    bool inside;

    if(checkHit(r, t, inside)){
        Vec4 hit = r.at(t);
        LightComponents l = this->lightComponents;
        if(checkerBoard){
            bool check;
            Vec4 localHit = getTransformation().getInverse() * hit;
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
                l.color = {};
                return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material};
            }
        }
        double red, green, blue;
        this->getColor(hit, red, green, blue);
        l.color = {red, green, blue, 0};

        return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material};
    }

    return {};
}

bool Plane::checkHit(Ray r, double &t, bool &inside) {
    // assume the plane is infinitely thin
    inside = false;
    return checkHit(r, t);
}

bool Plane::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);
    // Ray is not parallel to the plane
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();

        // Check if dimensions of plane are limited
        Vec4 hit = transformedRay.at(t);
        if(planeLength>0){
            if(hit.getX()>planeLength/2 or hit.getX()<-planeLength/2){
                t = -1;
            }
        }
        if(planeWidth>0){
            if(hit.getZ()>planeWidth/2 or hit.getZ()<-planeWidth/2){
                t = -1;
            }
        }
        return t>0;
    }
    return false;
}

bool Plane::checkHit(Ray r) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);
    // Ray is not parallel to the plane
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        return -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY()>0;
    }
    return false;
}

Vec4 Plane::calculateNormal(Vec4 hitPoint, bool inside) {
    if(inside)
        return Vec4::normalize((getTransformation().getForward() * Vec4({0, 1, 0, 0})) + Vec4::random(-0.5, 0.5) * material.roughness) * -1;
    return Vec4::normalize((getTransformation().getForward() * Vec4({0, 1, 0, 0})) + Vec4::random(-0.5, 0.5) * material.roughness);
}

void Plane::setCheckerBoardPattern(bool b, int size) {
    this->checkerBoard = b;
    this->checkerBoardSize = size;
}

void Plane::setSize(double l, double w) {
    this->planeLength = l;
    this->planeWidth = w;
}

void Plane::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    if(useColor){
        Shape::getColor(hitPoint, r, g, b);
    } else {
        Vec4 hit = t.getInverse()*hitPoint;

        int i = floor(fmod((planeLength/2)+hit.getX(), height));
        int j = floor(fmod((planeWidth/2)+hit.getZ(), width));

        int startPoint = i*3+j*width*3;

        r = (double)image.at(startPoint)/255;
        g = (double)image.at(startPoint+1)/255;
        b = (double)image.at(startPoint+2)/255;
    }
}
