#include "Shape.h"

Shape::Shape(Transformation t) : t(t) { }

const Transformation &Shape::getT() const {
    return t;
}
