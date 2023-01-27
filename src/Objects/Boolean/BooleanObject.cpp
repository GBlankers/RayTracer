#include "BooleanObject.h"

#include <utility>

BooleanObject::BooleanObject(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2) : Shape(Transformation{}, LightComponents{}, Material{}){
    this->s1 = std::move(s1);
    this->s2 = std::move(s2);
}

BooleanObject::BooleanObject(std::shared_ptr<Shape> s1, std::shared_ptr<Shape> s2, Transformation t) : Shape(t, LightComponents{}, Material{}){
    this->s1 = std::move(s1);
    this->s2 = std::move(s2);
}
