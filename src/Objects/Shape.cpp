#include "Shape.h"

/**
 * abstract shape class used to contain the general functions
 * @param t transformation to place the shape in the world space
 * @param R red color component, needs to be 0<=R<=1.0
 * @param G green color component, needs to be 0<=G<=1.0
 * @param B blue color component, needs to be 0<=B<=1.0
 */
Shape::Shape(Transformation t, double R, double G, double B) : t(t), r(R), g(G), b(B){
    assert(R>=0 && R<=1.0);
    assert(G>=0 && G<=1.0);
    assert(B>=0 && B<=1.0);
}

const Transformation &Shape::getT() const {
    return t;
}

double Shape::getR() const {
    return r;
}

double Shape::getG() const {
    return g;
}

double Shape::getB() const {
    return b;
}
