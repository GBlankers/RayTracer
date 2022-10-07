#include "Shape.h"
#include <iostream>

Shape::Shape(Transformation t) {
    this->t = t;
    std::cout << "Base shape class generated"<< std::endl;
}
