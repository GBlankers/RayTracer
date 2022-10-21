#include "Transformation.h"

void Transformation::addTranslation(double x, double y, double z) {
    Matrix4 temp;
    if(this->firstTransformation){
        this->forward.addTranslation(x, y, z);
        this->inverse.addTranslation(-x, -y, -z);
        this->firstTransformation = false;
    } else {
        temp.addTranslation(x, y, z);
        this->forward = temp*this->forward;
        temp.addTranslation(-x, -y, -z);
        this->inverse = temp*this->inverse;//*temp;
    }
}

void Transformation::addScaling(double sx, double sy, double sz) {
    Matrix4 temp;
    if(this->firstTransformation) {
        this->forward.addScaling(sx, sy, sz);
        this->inverse.addScaling(1/sx, 1/sy, 1/sz);
        this->firstTransformation = false;
    } else {
        temp.addScaling(sx, sy, sz);
        this->forward = temp*this->forward;
        temp.addScaling(1/sx, 1/sy, 1/sz);
        this->inverse = temp*this->inverse;//*temp;
    }
}

const Matrix4 &Transformation::getForward() const {
    return forward;
}

const Matrix4 &Transformation::getInverse() const{
    return inverse;
}
