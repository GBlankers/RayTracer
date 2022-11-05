#include "Cone.h"

Cone::Cone(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular, double specularComponent) :
    Shape(t, color, ambient, diffuse, specular, specularComponent) {}

Collision Cone::checkCollision(Ray r) {

    double t;

    if(checkHit(r, t)){
        return {r.at(t), t, this->getColor()};
    }
    return {{0, 0, 0, 0}, -1, {0, 0, 0, 0}};
}

bool Cone::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Check for hit with cone
    Vec4 rd = transformedRay.getDirectionVector();
    Vec4 rp = transformedRay.getStartPoint();

    double a = pow(rd.getX(), 2) + pow(rd.getZ(), 2) - pow(rd.getY(), 2);
    double b = rd.getX()*rp.getX()+rd.getZ()*rp.getZ()-rd.getY()*rp.getY();
    double c = pow(rp.getX(), 2) + pow(rp.getZ(), 2) - pow(rp.getY(), 2);

    t = (-b - sqrt(pow(b, 2)-(a*c)))/a;


    Vec4 hitPointL = transformedRay.at(t);

    // The hit with the cone is not inside the defined unit cone
    if(hitPointL.getY() > -1 and hitPointL.getY() < 0){
        return true;
    }
    // Check for hit with the bottom plane
    if(fabs(rd.getY()) > EPSILON){
        double t1 = (-rp.getY()-1)/rd.getY();

        // Check if hit in front of the eye
        if(t1>0){
            hitPointL = transformedRay.at(t1);
            // Check if the hit is inside the unit circle
            if(sqrt(pow(hitPointL.getX(), 2) + pow(hitPointL.getZ(), 2)) <= 1){
                t = t1;
                return true;
            }
        }
    }
    return false;

}

bool Cone::checkHit(Ray r) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Check for hit with cone
    Vec4 rd = transformedRay.getDirectionVector();
    Vec4 rp = transformedRay.getStartPoint();

    double a = pow(rd.getX(), 2) + pow(rd.getZ(), 2) - pow(rd.getY(), 2);
    double b = rd.getX()*rp.getX()+rd.getZ()*rp.getZ()-rd.getY()*rp.getY();
    double c = pow(rp.getX(), 2) + pow(rp.getZ(), 2) - pow(rp.getY(), 2);

    double t = (-b - sqrt(pow(b, 2)-(a*c)))/a;


    Vec4 hitPointL = transformedRay.at(t);

    // The hit with the cone is not inside the defined unit cone
    if(hitPointL.getY() > -1 and hitPointL.getY() < 0){
        return true;
    }
    // Check for hit with the bottom plane
    if(fabs(rd.getY()) > EPSILON){
        double t1 = (-rp.getY()-1)/rd.getY();

        // Check if hit in front of the eye
        if(t1>0){
            hitPointL = transformedRay.at(t1);
            // Check if the hit is inside the unit circle
            if(sqrt(pow(hitPointL.getX(), 2) + pow(hitPointL.getZ(), 2)) <= 1){
                t = t1;
                return true;
            }
        }
    }
    return false;
}

Vec4 Cone::calculateNormal(Vec4 hitPoint) {
    if(hitPoint.getY() == 0){
        return {0, 1, 0, 0};
    } else if (hitPoint.getY() == -1){
        return {0, -1, 0, 0};
    }
    Vec4 temp(2*hitPoint.getX(), -2*hitPoint.getY(), 2*hitPoint.getZ(), 0);
    return temp*(1/Vec4::length(temp));
}
