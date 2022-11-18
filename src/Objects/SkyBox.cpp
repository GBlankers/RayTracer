#include "SkyBox.h"

SkyBox::SkyBox() = default;

SkyBox::SkyBox(Vec4 color) {
    this->color=color;
}

Vec4 SkyBox::getColor(Vec4 direction) const{
    return color;
}
