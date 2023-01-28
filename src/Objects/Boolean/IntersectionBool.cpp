#include "IntersectionBool.h"

IntersectionBool::IntersectionBool(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) : BooleanObject(std::move(s1), std::move(s2)) {}
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

    // check if objects overlap
    // not -> just return the closest collision
    // else -> both objects are hit, find the closest t (with corresponding closest collision) and the furthest t

    // both objects hit
    if(tin1>0 and tin2>0){
        if(tout2>tout1){
            newT2 = tout2;
        }
        // first object is closer
        if(tin1<tin2){

        }
    }

}

bool IntersectionBool::checkHit(Ray r, double &t) {
    return false;
}
