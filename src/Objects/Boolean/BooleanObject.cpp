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

// TODO: need to be implemented in every boolean class
SingleColor *BooleanObject::getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) { return nullptr; }

bool BooleanObject::checkHit(Ray r, double &t, bool &inside, double &t2) { return false; }
Vec4 BooleanObject::calculateNormal(Vec4 hitPoint, bool inside) {return {};}
void BooleanObject::getColor(Vec4 hitPoint, double &r, double &g, double &b) {}
