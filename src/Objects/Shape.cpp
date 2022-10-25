#include "Shape.h"

/**
 * abstract shape class used to contain the general functions
 * @param t transformation to place the shape in the world space
 * @param R red color component, needs to be 0<=R<=1.0
 * @param G green color component, needs to be 0<=G<=1.0
 * @param B blue color component, needs to be 0<=B<=1.0
 */
Shape::Shape(Transformation t, Vec4 color) : t(t), color(color){
    assert(this->color.getX()>=0 && this->color.getX()<=1.0);
    assert(this->color.getY()>=0 && this->color.getY()<=1.0);
    assert(this->color.getZ()>=0 && this->color.getZ()<=1.0);
}

Vec4 Shape::getColor(Vec4 hit, double intensity) {
    return color*intensity;
}

const Transformation &Shape::getT() const {
    return t;
}

double Shape::getR() const {
    return color.getX();
}

double Shape::getG() const {
    return color.getY();
}

double Shape::getB() const {
    return color.getZ();
}
