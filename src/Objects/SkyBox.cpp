#include "SkyBox.h"

SkyBox::SkyBox() = default;

SkyBox::SkyBox(Color* color) {
    this->c = color;
}

Vec4 SkyBox::getColor(Vec4 direction) const{
    // uv-map
    double u = 0.5 + (atan2(direction.getZ(), direction.getX())/(2*M_PI));
    double v = 0.5 + asin(direction.getY()*-1)/M_PI;
    return c->getColor("sphere", u, v, Vec4(), Vec4());
}
