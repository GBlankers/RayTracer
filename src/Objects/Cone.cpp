#include "Cone.h"

Cone::Cone(const Transformation &t, const Vec4 &color) : Shape(t, color, 0.0) {}

Collision Cone::checkCollision(Ray r) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    Vec4 rd = transformedRay.getDirectionVector();
    Vec4 rp = transformedRay.getStartPoint();

    double a = pow(rd.getX(), 2) + pow(rd.getZ(), 2) - pow(rd.getY(), 2);
    double b = rd.getX()*rp.getX()+rd.getZ()*rp.getZ()-rd.getY()*rp.getY();
    double c = pow(rp.getX(), 2) + pow(rp.getZ(), 2) - pow(rp.getY(), 2);

    double t = (-b - sqrt(pow(b, 2)-(a*c)))/a;

    double temp;
    Vec4 hitPointL{};

    // Bottom plane
    if(rd.getY()!=0){
        temp = (-rp.getY()-1)/rd.getY();

        // Check if hit is closer than previous hit
        if(temp>0 and temp<t){
            hitPointL = transformedRay.at(temp);
            // Check if the hit is inside the unit circle
            if(sqrt(pow(hitPointL.getX(), 2) + pow(hitPointL.getZ(), 2)) <= 1){
                t = temp;
            }
        }
    }

    hitPointL = transformedRay.at(t);

    if(hitPointL.getY() >= -1 and hitPointL.getY() <= 0 and t > -1){
        return {r.at(t), t, this->getColor()};
    }
    return {{0, 0, 0, 0}, -1, {0, 0, 0, 0}};
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

bool Cone::checkHit(Ray r, double &t) {
    return false;
}
