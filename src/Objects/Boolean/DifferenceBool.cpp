#include "DifferenceBool.h"

#include <utility>

DifferenceBool::DifferenceBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) : BooleanObject(std::move(s1), std::move(s2)){}
DifferenceBool::DifferenceBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t) : BooleanObject(std::move(s1), std::move(s2), t) {}

Collision DifferenceBool::checkCollision(Ray r) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Implementation for basic case
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT(), tout2= c2.getT2(), newT1, newT2;

    // Hit with the positive object
    if(tin1 > 0){
        // No hit with the negative object or the positive object is hit first or negative and positive do not touch
        if(tin2 < 0 or (tin1 < tin2 and tin2 > 0) or tout2 < tin1) return c1;
        // Negative object ends inside the positive object
        if(tout2 < tout1){newT2 = tout1;newT1 = tout2;}
        // Negative object consumes the positive object => nothing will be hit
        else {newT1 = -1; newT2 = -1;}

        return {transformedRay, newT1, s2->calculateNormal(transformedRay.at(newT1), true), false, c1.getLightComponents(), c1.getMaterial(), newT2};
    }

    return {};
}

bool DifferenceBool::checkHit(Ray r, double &t) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }
    // Implementation for basic case
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT(), tout2= c2.getT2();

    // Hit with the positive object
    if(tin1 > 0){
        if(tout1 <= 0 and tout2 <= 0) {t = -1; return false;}
        // No hit with the negative object or the positive object is hit first or negative and positive do not touch
        if(tin2 < 0 or (tin1 < tin2 and tin2 > 0) or tout2 < tin1) {t = tin1;return true;}
        // Negative object ends inside the positive object
        if(tout2 < tout1){t = tout2; return true;}
        // Negative object consumes the positive object => nothing will be hit
        t = -1;
        return false;
    }
    t = -1;
    return false;
}

// Default implementation as these will be used from the child objects.
Vec4 DifferenceBool::calculateNormal(Vec4 hitPoint, bool inside) {return {};}
void DifferenceBool::getColor(Vec4 hitPoint, double &r, double &g, double &b) {}
bool DifferenceBool::checkHit(Ray r, double &t, bool &inside, double &t2) {return false;}
