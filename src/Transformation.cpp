#include "Transformation.h"

void Transformation::addTranslation(double x, double y, double z) {
    if(firstTransformation){
        this->forward.addTranslation(x, y, z);
        this->inverse.addTranslation(-x, -y, -z);
        firstTransformation = false;
    } else {
        Matrix4 tempForward;
        Matrix4 tempInverse;
        tempForward.addTranslation(x, y, z);
        tempInverse.addTranslation(-x, -y, -z);
        this->forward = tempForward*this->forward;
        this->inverse = tempInverse* this->inverse;
    }

}

void Transformation::addScaling(double sx, double sy, double sz) {
    this->forward.addScaling(sx, sy, sz);
    this->inverse.addScaling(1/sx, 1/sy, 1/sz);
}
