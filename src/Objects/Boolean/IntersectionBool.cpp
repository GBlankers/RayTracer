#include "IntersectionBool.h"

IntersectionBool::IntersectionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t) : BooleanObject(std::move(s1), std::move(s2),t) {}

Collision IntersectionBool::checkCollision(Ray r) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Get all collisions and t's of in and out
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT(), tout2= c2.getT2(), newT1, newT2;

    if(tin1 > 0 and tin2 > 0){ // intersection only possible when both objects are hit
        if(tin1 < tin2){ // object 1 is hit first
            if(c1.isInside() and c2.isInside()){ // ray is inside both the objects
                newT1 = tin1; newT2 = tin1;
                return {r, newT1, s1->calculateNormal(r.at(newT1), false), false, c1.getLightComponents(), c1.getMaterial(), newT2};
            } else if(c2.isInside()){
                newT1 = tin1; newT2 = tin2;
                return {r, newT1, s1->calculateNormal(r.at(newT1), false), false, c1.getLightComponents(), c1.getMaterial(), newT2};
            }else if(tin2 > tout1 or c1.isInside()){ // there is no overlap
                return {};
            }
            // Ray comes from the outside
            if(tin2 < tout1){ // check if there is overlap
                newT1 = tin2;
            } else { // no overlap
                return {};
            }

            // check if the objects are fully consumed
            if(tout1 < tout2){
                newT2 = tout1;
            } else {
                newT2 = tout2;
            }
            return {r, newT1, s2->calculateNormal(r.at(newT1), false), false, c2.getLightComponents(), c2.getMaterial(), newT2};
        } else { // the second object is hit first
            if(c1.isInside() and c2.isInside()){ // ray is inside both objects
                newT1 = tin2; newT2 = tin2;
                return {r, newT1, s2->calculateNormal(r.at(newT1), false), false, c2.getLightComponents(), c2.getMaterial(), newT2};
            } else if(c1.isInside()){
                newT1 = tin2; newT2 = tin1;
                return {r, newT1, s1->calculateNormal(r.at(newT1), false), false, c1.getLightComponents(), c1.getMaterial(), newT2};
            }else if(tin2 > tout1 or c2.isInside()){ // there is no overlap
                return {};
            }
            // Check if there is overlap
            if(tin1 < tout2){
                newT1 = tin1;
            } else {
                return {};
            }
            // check if the objects are fully consumed
            if(tout2 < tout1){
                newT2 = tout2;
            } else {
                newT2 = tout1;
            }
            return {r, newT1, s1->calculateNormal(r.at(newT1), false), false, c1.getLightComponents(), c1.getMaterial(), newT2};
        }
    }
    return {};
}

bool IntersectionBool::checkHit(Ray r, double &t) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Get all collisions and t's of in and out
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT();

    if(tin1 > 0 and tin2 > 0){ // intersection only possible when both objects are hit
        if(tin1 < tin2){ // object 1 is hit first
            if(c1.isInside() and c2.isInside()){ // ray is inside both objects
                t = tin1;
                return true;
            } else if(c2.isInside()){
                t = tin1;
                return true;
            }else if(tin2 > tout1 or c1.isInside()){ // there is no overlap
                return false;
            }
            t = tin2;
            return true;
        } else {
            if(c1.isInside() and c2.isInside()){ // ray is inside both objects
                t = tin2;
                return true;
            } else if(c1.isInside()){
                t = tin2;
                return true;
            }else if(tin2 > tout1 or c2.isInside()){ // there is no overlap
                return false;
            }
            t = tin1;
            return true;
        }
    }
    return false;
}

bool IntersectionBool::isPointInside(Vec4 hitPoint) const {
    return s1->isPointInside(hitPoint) and s2->isPointInside(hitPoint);
}

SingleColor *IntersectionBool::getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) {
    if(s1->isPointInside(hitPoint)){
        return s1->getBooleanDifferenceColor(hitPoint, l);
    } else {
        return s2->getBooleanDifferenceColor(hitPoint, l);
    }
}
