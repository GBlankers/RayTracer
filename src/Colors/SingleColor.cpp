#include "SingleColor.h"

SingleColor::SingleColor(Vec4 c) {
    assert(c.getX()>=0 && c.getX()<=1.0);
    assert(c.getY()>=0 && c.getY()<=1.0);
    assert(c.getZ()>=0 && c.getZ()<=1.0);
    this->c = c;
}

Vec4 SingleColor::getColor(const std::string &objectType, double u, double v) {
    return c;
}

Vec4 SingleColor::getColor() {
    return c;
}
