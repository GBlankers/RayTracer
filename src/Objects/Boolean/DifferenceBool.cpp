#include "DifferenceBool.h"

DifferenceBool::DifferenceBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) : BooleanObject(std::move(s1), std::move(s2)){}
DifferenceBool::DifferenceBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t) : BooleanObject(std::move(s1), std::move(s2), t) {}

Collision DifferenceBool::checkCollision(Ray r) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Get all collisions and t's of in and out
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT(), tout2= c2.getT2(), newT1, newT2;

    // Hit with the positive object
    if(tin1 > 0){
        // no hit with the negative object -> nothing will be deleted
        if(tin2 < 0) return c1;
        // negative object is hit first
        if(tin2 < tin1){
            if(c1.isInside() and c2.isInside()){ // ray inside both objects
                newT1 = tin2;
                // The negative object part is hit -> project the color of the positive object on the negative object to
                // get more realistic textures
                LightComponents temp = s1->getLightComponents();
                temp.color = s2->getBooleanDifferenceColor(r.at(newT1), s1->getLightComponents());
                return {r, newT1, s2->calculateNormal(r.at(newT1), true), false, temp, c1.getMaterial()};
            } else if(c1.isInside()){ // ray inside the positive object
                newT1 = tin2;
                LightComponents temp = s1->getLightComponents();
                temp.color = s2->getBooleanDifferenceColor(r.at(newT1), s1->getLightComponents());
                return {r, newT1, s2->calculateNormal(r.at(newT1), false), true, temp, c1.getMaterial()};
            } else if(c2.isInside()){ // ray inside the negative object
                return {};
            } else if(tin1 < tout2){ // ray outside and overlap
                newT1 = tout2;
                newT2 = tout1;
                LightComponents temp = s1->getLightComponents();
                temp.color = s2->getBooleanDifferenceColor(r.at(newT1), s1->getLightComponents());
                return {r, newT1, s2->calculateNormal(r.at(newT1), true), false, temp, c1.getMaterial(), newT2};
            } else { // ray outside and no overlap
                return c1;
            }
        }
        // Positive object is hit first
        // ray inside both objects and positive hit first -> will be deleted by negative object
        if(c1.isInside() and c2.isInside()) return {};
        else if(c2.isInside()){ // inside the negative object
            newT1 = tin2;
            newT2 = tout1;
            LightComponents temp = s1->getLightComponents();
            temp.color = s2->getBooleanDifferenceColor(r.at(newT1), s1->getLightComponents());
            return {r, newT1, s2->calculateNormal(r.at(newT1), true), false, temp, c1.getMaterial(), newT2};
        }
        return c1;

    }

    return {};
}

// TODO : check different implementation
bool DifferenceBool::checkHit(Ray r, double &t) {
    // Check for transformation at boolean object level
    Ray transformedRay = r;
    if(!this->t.getEmpty()){
        Matrix4 inverse = getTransformation().getInverse();
        transformedRay = r.transform(inverse);
    }

    // Get all collisions and t's of in and out
    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
    double tin1 = c1.getT(), tout1 = c1.getT2(), tin2 = c2.getT(), tout2 = c2.getT2();

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


    // DOES NOT WORK
//    // Check for transformation at boolean object level
//    Ray transformedRay = r;
//    if(!this->t.getEmpty()){
//        Matrix4 inverse = getTransformation().getInverse();
//        transformedRay = r.transform(inverse);
//    }
//
//    // Get all collisions and t's of in and out
//    Collision c1 = s1->checkCollision(transformedRay), c2 = s2->checkCollision(transformedRay);
//    double tin1 = c1.getT(), tin2 = c2.getT(), tout2= c2.getT2();
//
//    // Hit with the positive object
//    if(tin1 > 0){
//        // no hit with the negative object -> nothing will be deleted
//        if(tin2 < 0){t = tin1; return true;}
//        // negative object is hit first
//        if(tin2 < tin1){
//            if(c1.isInside() and c2.isInside()){ // ray inside both objects
//                t = tin2;
//                return true;
//            } else if(c1.isInside()){ // ray inside the positive object
//                t = tin2;
//                return true;
//            } else if(c2.isInside()){ // ray inside the negative object
//                t = -1;
//                return false;
//            } else if(tin1 < tout2){ // ray outside and overlap
//                t = tout2;
//                return true;
//            } else { // ray outside and no overlap
//                t = tin1;
//                return true;
//            }
//        }
//        // Positive object is hit first
//        // ray inside both objects and positive hit first -> will be deleted by negative object
//        if(c1.isInside() and c2.isInside()){ t = -1; return false;}
//        else if(c2.isInside()){ // inside the negative object
//            t = tin2;
//            return true;
//        }
//        t = tin1;
//        return true;
//    }
//    t = -1;
//    return false;
}

const LightComponents &DifferenceBool::getLightComponents() const {
    return s1->getLightComponents();
}
