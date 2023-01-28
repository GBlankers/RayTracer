#include "UnionBool.h"

UnionBool::UnionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) : BooleanObject(std::move(s1), std::move(s2)) {}
UnionBool::UnionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t) : BooleanObject(std::move(s1), std::move(s2),t) {}

Collision UnionBool::checkCollision(Ray r) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Get all collisions and t's of in and out
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT(), tout2= c2.getT2(), newT1 = -1, newT2 = -1;

    // 1. both objects hit & overlap
        // -> tin from first object, tout from last object
    // 2. both objects hit & no overlap
        // -> tin and tout from first object
    // 3. only 1 object hit
        // -> tin and tout from only hit object
    // 4. inside the objects

    // both objects hit, ray outside objects
    if(tin1>0 and tin2>0){
        // check which object is closer
        if(tin1 < tin2){ // first object is closer
            newT1 = tin1;
            // check for overlap and if inside
            if(tout1 < 0 and tout2 < 0) { // ray inside both objects
                newT2 = tin2;
            }else if(tout2 < 0){ // ray inside second object
                newT2 = tout1;
            }else if(tin2 < tout1){ // ray outside both objects and overlap
                newT2 = tout2;
            } else { // ray outside both objects and no overlap
                newT2 = tout1;
            }
            return {r, newT1, s1->calculateNormal(r.at(newT1), false), false, c1.getLightComponents(), c1.getMaterial(), newT2};
        } else { // second object is closer
            newT1 = tin2;
            // check for overlap and if inside
            if(tout1 < 0 and tout2 < 0) { // ray inside both objects
                newT2 = tin1;
            }else if(tout1 < 0){ // ray inside first object
                newT2 = tout2;
            }else if(tin1 < tout2){ // ray outside both objects and overlap
                newT2 = tout1;
            } else { // ray outside both objects and no overlap
                newT2 = tout2;
            }
            return {r, newT1, s2->calculateNormal(r.at(newT1), false), false, c2.getLightComponents(), c2.getMaterial(), newT2};
        }
    } else if (tin1>0) { // Only 1 object is hit
        return {r, tin1, s1->calculateNormal(r.at(tin1), false), false, c1.getLightComponents(), c1.getMaterial(), tout1};
    } else if (tin2>0){
        return {r, tin2, s2->calculateNormal(r.at(tin2), false), false, c2.getLightComponents(), c2.getMaterial(), tout2};
    }
    return {};
}

bool UnionBool::checkHit(Ray r, double &t) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Get all collisions and t's of in and out
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tin2 = c2.getT();

    if(tin1>0 and tin2>0){
        // check which object is closer
        if(tin1 < tin2){ // first object is closer
            t = tin1;
            return true;
        } else { // second object is closer
            t = tin2;
            return true;
        }
    } else if (tin1>0) { // Only 1 object is hit
        t = tin1;
        return true;
    } else if (tin2>0){
        t = tin2;
        return true;
    }
    return false;
}

const LightComponents &UnionBool::getLightComponents() const {
    return s1->getLightComponents();
}

SingleColor *UnionBool::getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) {
    if(s1->isPointInside(hitPoint)){
        return s1->getBooleanDifferenceColor(hitPoint, l);
    } else {
        return s2->getBooleanDifferenceColor(hitPoint, l);
    }
}

bool UnionBool::isPointInside(Vec4 hitPoint) const {
    return s1->isPointInside(hitPoint) or s2->isPointInside(hitPoint);
}
