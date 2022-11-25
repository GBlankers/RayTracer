#include "Cone.h"

Cone::Cone(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
           double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex) :
        Shape(t, color, ambient, diffuse, specular, specularComponent, reflectivity, roughness, transparency, refractiveIndex) {}

Cone::Cone(const Transformation &t, const std::string& path, double ambient, double diffuse, double specular,
           double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex) :
        Shape(t, path, ambient, diffuse, specular, specularComponent, reflectivity, roughness, transparency, refractiveIndex) {}

Collision Cone::checkCollision(Ray r) {
    double t;
    bool inside;

    if(checkHit(r, t, inside)){
        double red, green, blue;
        Vec4 hit = r.at(t);
        this->getColor(hit, red, green, blue);

        return {hit, t, {red, green, blue, 0}, Vec4::normalize(calculateNormal(hit, inside)+Vec4::random(-0.5, 0.5) * roughness),
                inside, reflectivity, transparency, refractiveIndex};
    }
    return {};
}


bool Cone::checkHit(Ray r, double &t, bool &inside) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Check if ray inside the cone
    Vec4 rayStart = transformedRay.getStartPoint();
    if(pow(rayStart.getX(), 2)+pow(rayStart.getZ(), 2) <= pow(rayStart.getY(), 2) and rayStart.getY() <=0 and rayStart.getY()>=-1){
        inside = true;
    } else {
        inside = false;
    }

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

bool Cone::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getT().getInverse();
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
    Matrix4 inverse = getT().getInverse();
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
                return true;
            }
        }
    }
    return false;
}

Vec4 Cone::calculateNormal(Vec4 hitPoint, bool inside) {
    int in = 1;
    if(inside)
        in = -1;

    Vec4 localHit = getT().getInverse()*hitPoint;
    if(fabs(localHit.getY()) < EPSILON){
        return Vec4::normalize(getT().getForward()*Vec4{0, 1, 0, 0})*in;
    } else if (fabs(localHit.getY()+1) < EPSILON){
        return Vec4::normalize(getT().getForward()*Vec4{0, -1, 0, 0})*in;
    }
    return Vec4::normalize(getT().getForward()*Vec4{2*localHit.getX(), -2*localHit.getY(), 2*localHit.getZ(), 0})*in;
}
