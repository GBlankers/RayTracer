#include "Cone.h"
#include <iostream>

Cone::Cone(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

Collision Cone::checkCollision(Ray r) {
    double t, t2;
    bool inside;

    if(checkHit(r, t, inside, t2)){
        double red, green, blue;
        LightComponents l = this->lightComponents;
        Vec4 hit = r.at(t);
        this->getColor(hit, red, green, blue);
        l.color = new SingleColor(Vec4{red, green, blue, 0});

        return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material, t2};
    }
    return {};
}


bool Cone::checkHit(Ray r, double &t, bool &inside, double &t2) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
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

    if(pow(b, 2)-a*c < 0) return false; // negative discriminant

    double tempT1 = -1, tempT2 = -1, tempT3 = -1, tempT4 = -1;
    std::vector<double> tList;

    // Intersections with the cone
    tempT1 = (-b - sqrt(pow(b, 2)-(a*c)))/a;
    tempT2 = (-b + sqrt(pow(b, 2)-(a*c)))/a;
    // Intersection with the bottom plane
    if(fabs(rd.getY())>EPSILON){ tempT3 = (-rp.getY()-1)/rd.getY(); }
    // If a == 0 -> ray parallel with the cone legs
    if(a == 0){ tempT4 = -c/b; }

    // Check if these are inside the cone -> add to list
    if(tempT1 > 0 and insideUnitCone(transformedRay.at(tempT1))) tList.emplace_back(tempT1);
    if(tempT2 > 0 and insideUnitCone(transformedRay.at(tempT2))) tList.emplace_back(tempT2);
    if(tempT3 > 0 and insideUnitCone(transformedRay.at(tempT3))) tList.emplace_back(tempT3);
    if(tempT4 > 0 and insideUnitCone(transformedRay.at(tempT4))) tList.emplace_back(tempT4);

    if(tList.empty()){ return false; }

    std::sort(tList.begin(), tList.end());

    if(tList.size() > 1){
        t = tList[0];
        t2 = tList[1];
        return true;
    } else {
        t = tList[0];
        t2 = -1;
        return true;
    }

    return false;
}

bool Cone::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Check for hit with cone
    Vec4 rd = transformedRay.getDirectionVector();
    Vec4 rp = transformedRay.getStartPoint();
    double a = pow(rd.getX(), 2) + pow(rd.getZ(), 2) - pow(rd.getY(), 2);
    double b = rd.getX()*rp.getX()+rd.getZ()*rp.getZ()-rd.getY()*rp.getY();
    double c = pow(rp.getX(), 2) + pow(rp.getZ(), 2) - pow(rp.getY(), 2);

    if(pow(b, 2)-a*c < 0) return false; // negative discriminant

    double tempT1 = -1, tempT2 = -1, tempT3 = -1, tempT4 = -1;
    std::vector<double> tList;

    // Intersections with the cone
    tempT1 = (-b - sqrt(pow(b, 2)-(a*c)))/a;
    tempT2 = (-b + sqrt(pow(b, 2)-(a*c)))/a;
    // Intersection with the bottom plane
    if(fabs(rd.getY())>EPSILON){ tempT3 = (-rp.getY()-1)/rd.getY(); }
    // If a == 0 -> ray parallel with the cone legs
    if(a == 0){ tempT4 = -c/b; }

    // Check if these are inside the cone -> add to list
    if(tempT1 > 0 and insideUnitCone(transformedRay.at(tempT1))) tList.emplace_back(tempT1);
    if(tempT2 > 0 and insideUnitCone(transformedRay.at(tempT2))) tList.emplace_back(tempT2);
    if(tempT3 > 0 and insideUnitCone(transformedRay.at(tempT3))) tList.emplace_back(tempT3);
    if(tempT4 > 0 and insideUnitCone(transformedRay.at(tempT4))) tList.emplace_back(tempT4);

    if(tList.size() > 1){ return true; }

    return false;
}

Vec4 Cone::calculateNormal(Vec4 hitPoint, bool inside) {
    Vec4 localHit = t.getInverse() * hitPoint;
    // Calculate the normal in local coordinates + uv-mapping
    Vec4 normal;
    double u, v;
    if(localHit.getY() <= -1+EPSILON){ // Hit the bottom plane
        u = (1+localHit.getX())/2;
        v = (1+localHit.getZ())/2;
        normal = inside ? Vec4{0, -1, 0, 0} : Vec4{0, 1, 0, 0};
    } else { // Hit the cone
        u = (1+atan2(localHit.getX(), localHit.getZ())/M_PI)/2;
        v = fabs(localHit.getY());
        normal = inside ? Vec4{2 * localHit.getX(), -2 * localHit.getY(), 2 * localHit.getZ(), 0} :
                 Vec4{2 * localHit.getX(), -2 * localHit.getY(), 2 * localHit.getZ(), 0} * -1;
    }
    // Manipulate normal + transform to world coordinates + normalize
    return Vec4::normalize(t.getForward()*material.manipulateNormal(normal, u, v, hitPoint));
}

void Cone::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    Vec4 localHit = t.getInverse()*hitPoint;
    // uv-mapping
    double u, v;
    if(localHit.getY() <= -1+EPSILON){
        u = (1+localHit.getX())/2;
        v = (1+localHit.getZ())/2;
    } else {
        u = (1+atan2(localHit.getX(), localHit.getZ())/M_PI)/2;
        v = fabs(localHit.getY());
    }
    // get color components
    Vec4 c = lightComponents.color->getColor(u, v, localHit, hitPoint);
    r = c.getX();
    g = c.getY();
    b = c.getZ();
}

SingleColor* Cone::getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) {
    Vec4 localHit = t.getInverse()*hitPoint;
    // uv-mapping
    double u, v;
    if(localHit.getY() <= -1+EPSILON){
        u = (1+localHit.getX())/2;
        v = (1+localHit.getZ())/2;
    } else {
        u = (1+atan2(localHit.getX(), localHit.getZ())/M_PI)/2;
        v = fabs(localHit.getY());
    }
    // get color components
    Vec4 c = l.color->getColor(u, v, localHit, hitPoint);
    return new SingleColor({c.getX(), c.getY(), c.getZ(), 0});
}

bool Cone::insideUnitCone(Vec4 hitPoint) {
    // Hit with cone
    if(hitPoint.getY() <= 0 and hitPoint.getY() > -1
                and (pow(hitPoint.getX(), 2) + pow(hitPoint.getZ(), 2) - pow(hitPoint.getY(), 2) < EPSILON)) return true;
    // Hit with bottom plane
    if(sqrt(pow(hitPoint.getX(), 2) + pow(hitPoint.getZ(), 2)) <= 1 and fabs(hitPoint.getY()+1) <= EPSILON) return true;

    return false;
}

bool Cone::isPointInside(Vec4 hitPoint) const {
    Vec4 localPoint = t.getInverse()*hitPoint;
    return insideUnitCone(localPoint);
}
