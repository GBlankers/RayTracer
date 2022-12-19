#include "SingleColor.h"

SingleColor::SingleColor(Vec4 c) {
    assert(c.getX()>=0 && c.getX()<=1.0);
    assert(c.getY()>=0 && c.getY()<=1.0);
    assert(c.getZ()>=0 && c.getZ()<=1.0);
    this->c = c;
}

Vec4 SingleColor::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    return c;
}
