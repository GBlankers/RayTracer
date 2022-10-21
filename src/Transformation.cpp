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

void Transformation::addRotationX(double thetaX) {
    Matrix4 temp;
    if(this->firstTransformation) {
        this->forward.addRotationX(thetaX);
        this->inverse.addRotationX(-1*thetaX);
        this->firstTransformation = false;
    } else {
        temp.addRotationX(thetaX);
        this->forward = temp*this->forward;
        temp.addRotationX(-thetaX);
        this->inverse = temp*this->inverse;//*temp;
    }
}

void Transformation::addRotationY(double thetaY) {
    Matrix4 temp;
    if(this->firstTransformation) {
        this->forward.addRotationY(thetaY);
        this->inverse.addRotationY(-1*thetaY);
        this->firstTransformation = false;
    } else {
        temp.addRotationY(thetaY);
        this->forward = temp*this->forward;
        temp.addRotationY(-1*thetaY);
        this->inverse = temp*this->inverse;//*temp;
    }
}

void Transformation::addRotationZ(double thetaZ) {

}

const Matrix4 &Transformation::getForward() const {
    return forward;
}

const Matrix4 &Transformation::getInverse() const{
    return inverse;
}
